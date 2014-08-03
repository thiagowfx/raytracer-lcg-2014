#include "RaytracerApi.h"

namespace Raytracer {
  Api::Api() :
    w(new World) {
    w->set_camera(new Camera());
    w->camera_ptr->set_eye_position(Vector3d(0.0, 50.0, 50.0));

    w->add_light(new Raytracer::PointLight(Vector3d(100.0, 100.0, 100.0)));
    w->add_light(new Raytracer::PointLight(Vector3d(-50.0, 30.0, -20.0)));

    Raytracer::Plane *pl0 = new Raytracer::Plane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
    w->add_object(pl0);
    pl0->set_material(new Phong(light_gray));

    Raytracer::Sphere* sp0 = new Raytracer::Sphere(Vector3d(-40.0, 0.0, 0.0), 10);
    w->add_object(sp0);
    sp0->set_material(new Phong(red));

    Raytracer::Sphere* sp1 = new Raytracer::Sphere(Vector3d(40.0, 0.0, 0.0), 10);
    w->add_object(sp1);
    sp1->set_material(new Phong(blue));

    Raytracer::Sphere* sp2 = new Raytracer::Sphere(Vector3d(0.0, 0.0, -40.0), 10);
    w->add_object(sp2);
    sp2->set_material(new Phong(green));

    Raytracer::Sphere* sp3 = new Raytracer::Sphere(Vector3d(0.0, 0.0, 40.0), 10);
    w->add_object(sp3);
    sp3->set_material(new Phong(yellow));

    Raytracer::Torus *tor0 = new Raytracer::Torus(20.0, 10.0);
    w->add_object(tor0);
    tor0->set_material(new Phong(light_gray));
    
    Raytracer::Compound *cp0 = new Raytracer::Compound();
    cp0->add_object(new Raytracer::OpenCylinder(60.0, 90.0, 20.0));
    cp0->add_object(new Raytracer::Sphere(Vector3d(0.0, 90.0, 0.0), 20.0));
    cp0->set_material(new Matte(red));
    w->add_object(cp0);

    // std::clock_t time_begin = clock();
    // vector<Raytracer::PrimitivaDaniel*> vp = Raytracer::PrimitivaDaniel::loadPly("../lib/ply/camera.ply");
    // vector<Raytracer::PrimitivaDaniel*> vp = Raytracer::PrimitivaDaniel::generic("../lib/ply/CUBE");
    // double elapsed_secs = double(clock() - time_begin) / CLOCKS_PER_SEC * 1000;
    // printf("INFO: Extraction took %.2lf ms\n", elapsed_secs);
    // for (unsigned i = 0; i < vp.size(); ++i) {
    //   if (i & 1) {
    //     vp[i]->set_material(new Matte(red));
    //   }
    //   else {
    //     vp[i]->set_material(new Matte(blue));
    //   }
    //   w->add_object(vp[i]);
    // }

  }

  Api::~Api() {
    delete w;
  }

  Vector3d Api::carthesian_to_spherical(const Vector3d& c) {
    /* Carthesian coordinates: c(0) = x, c(1) = y, c(2) = z. */

    /* Spherical coordinates. */
    Vector3d s;

    /* Radius (r). Between zero and +infinity. */
    s(0) = c.norm();

    /* phi */
    s(1) = atan2(c(2), c(0)); // y -> z

    /* theta */
    s(2) = acos(c(1) / s(0)); // z -> y

    return s;
  }

  Vector3d Api::spherical_to_carthesian(const Vector3d& s) {
    /* Spherical coordinates: s(0) = r, s(1) = phi, s(2) = theta. */

    /* Carthesian coordinates. */
    Vector3d c;

    /* x */
    c(0) = s(0) * sin(s(2)) * cos(s(1));

    /* z */
    c(2) = s(0) * sin(s(2)) * sin(s(1)); // c(2) --> c(1)

    /* y */
    c(1) = s(0) * cos(s(2));  // c(1) --> c(2)

    return c;
  }


  QColor Api::rgbcolor_to_qcolor(const RGBColor& color) {
    QColor qcolor;
    qcolor.setRgbF(color.r, color.g, color.b);
    return qcolor;
  }

  RGBColor Api::qcolor_to_rgbcolor(const QColor& color) {
    return RGBColor(color.redF(), color.greenF(), color.blueF());
  }

  void Api::set_hres(int hres) {
    w->vp.set_hres(hres);
  }

  int Api::get_hres() {
    return w->vp.hres;
  }

  void Api::set_vres(int vres) {
    w->vp.set_vres(vres);
  }

  int Api::get_vres() {
    return w->vp.vres;
  }

  void Api::set_pixel_size(double size) {
    w->vp.set_pixel_size(size);
  }

  double Api::get_pixel_size() {
    return w->vp.pixel_size;
  }

  void Api::set_gamma(double gamma)   {
    w->vp.set_gamma(gamma);
  }

  double Api::get_gamma() {
    return 1.0 / w->vp.inv_gamma;
  }

  void Api::set_out_of_gamut(bool gamut) {
    w->vp.set_out_of_gamut(gamut);
  }

  bool Api::get_out_of_gamut() {
    return w->vp.out_of_gamut;
  }

  void Api::set_max_depth(int depth) {
    w->vp.set_max_depth(depth);
  }

  int Api::get_max_depth() {
    return w->vp.max_depth;
  }

  void Api::set_sampler(QString name, int samples) {
    Sampler* sampler;
    if (name == "Hammersley")
      w->vp.set_sampler(new Hammersley(samples));
    else if (name == "Jittered")
      w->vp.set_sampler(new Jittered(samples));
    else if (name == "MultiJittered")
      w->vp.set_sampler(new MultiJittered(samples));
    else if (name == "NRooks")
      w->vp.set_sampler(new NRooks(samples));
    else if (name == "PureRandom")
      w->vp.set_sampler(new PureRandom(samples));
    else // if (name == "Regular")
      w->vp.set_sampler(new Regular(samples));
  }

  int Api::get_number_of_samples() {
    return w->vp.sampler_ptr->get_number_of_samples();
  }

  const char* Api::get_sampler_type() {
    return w->vp.sampler_ptr->to_string();
  }

  QStringListModel* Api::get_sampler_type_model() {
    return new QStringListModel(QStringList() <<
                                "Hammersley" <<
                                "Jittered" <<
                                "MultiJittered" <<
                                "NRooks" <<
                                "PureRandom" <<
                                "Regular");
  }

  void Api::set_tracer_type(QString name) {
    Tracer* tracer;
    if (name == "AreaLighting")
      w->set_tracer(new AreaLighting(w));
    else if (name == "MultipleObjects")
      w->set_tracer(new MultipleObjects(w));
    else // if (name == "Whitted")
      w->set_tracer(new Whitted(w));
  }

  const char *Api::get_tracer_type() {
    return w->tracer_ptr->to_string();
  }

  QStringListModel* Api::get_tracer_type_model() {
    return new QStringListModel(QStringList() <<
                                "AreaLighting" <<
                                "MultipleObjects" <<
                                "Whitted");
  }

  void Api::set_background_color(QColor color) {
    w->set_background_color(qcolor_to_rgbcolor(color));
  }

  QColor Api::get_background_color() {
    return rgbcolor_to_qcolor(w->background_color);
  }

  unsigned Api::render_scene() {
    return w->camera_ptr->render_scene(w, get_rendered_image());
  }

  const char* Api::get_rendered_image() {
    return "renderedImage.png";
  }

  void Api::set_eye_carthesian(Vector3d v) {
    w->camera_ptr->set_eye_position(v);
  }

  void Api::set_eye_carthesian(double x, double y, double z) {
    set_eye_carthesian(Vector3d(x,y,z));
  }

  void Api::set_eye_spherical_relatively(double dr, double dphi, double dtheta) {
    Vector3d s = carthesian_to_spherical(w->camera_ptr->get_eye_position());
    s(0) += dr;
    s(1) += dphi;
    s(2) += dtheta;
    set_eye_carthesian(spherical_to_carthesian(s));
  }

  const char* Api::get_eye_carthesian_coordinates() {
    Vector3d v = w->camera_ptr->get_eye_position();
    sprintf(buffer, "(%.2lf, %.2lf, %.2lf)", v(0), v(1), v(2));
    return buffer;
  }

  const char *Api::get_eye_spherical_coordinates() {
    Vector3d v = carthesian_to_spherical(w->camera_ptr->get_eye_position());
    sprintf(buffer, "(%.2lf, %.2lfº, %.2lfº)", v(0), v(1) * (180.0 * INV_PI), v(2) * (180.0 * INV_PI));
    return buffer;
  }

  void Api::set_ambient_light(QString name, QColor color, double radiance) {
    Ambient* ambient;
    if (name == "Ambient") {
      ambient = new Ambient();
    }
    else { // if (name == "AmbientOccluder")
      ambient = new AmbientOccluder();
    }
    ambient->set_color(qcolor_to_rgbcolor(color));
    ambient->set_radiance(radiance);
    w->set_ambient_light(ambient);
  }

  const char *Api::get_ambient_light_type() {
    return w->ambient_ptr->to_string();
  }

  QStringListModel *Api::get_ambient_light_type_model() {
    return new QStringListModel(QStringList() <<
                                "Ambient" <<
                                "AmbientOccluder");
  }

  QColor Api::get_ambient_light_color() {
    return rgbcolor_to_qcolor(w->ambient_ptr->get_color());
  }

  double Api::get_ambient_light_radiance() {
    return w->ambient_ptr->get_radiance();
  }

  void Api::zoom_set(double z) {
    w->camera_ptr->set_zoom(z);
  }

  void Api::zoom_increase(double d) {
    w->camera_ptr->set_zoom(w->camera_ptr->get_zoom() * d);
  }

  void Api::zoom_decrease(double d) {
    w->camera_ptr->set_zoom(w->camera_ptr->get_zoom() / d);
  }

  double Api::zoom_get() const {
    return w->camera_ptr->get_zoom();
  }

  void Api::set_camera_distance(double d) {
    w->camera_ptr->set_distance(d);
  }

  double Api::get_camera_distance() const {
    return w->camera_ptr->get_distance();
  }

}
