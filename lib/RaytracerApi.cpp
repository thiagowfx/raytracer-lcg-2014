#include "RaytracerApi.h"

namespace Raytracer {
  Api::Api() :
    w(new World)
  {
    Raytracer::Pinhole* pinhole = new Pinhole();
    pinhole->set_eye(Vector3d(150.0, 150.0, 150.0));
    pinhole->compute_uvw();
    w->set_camera(pinhole);

    Raytracer::Sphere* sp0 = new Raytracer::Sphere(Vector3d::Zero(), 50);
    sp0->set_color(red);
    sp0->set_material(Matte::dummy(red));
    w->add_object(sp0);

    Raytracer::Plane *pl0 = new Raytracer::Plane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
    pl0->set_color(gray);
    pl0->set_material(Matte::dummy(gray));
    w->add_object(pl0);
  }

  Api::~Api() {
    delete w;
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
    return w->vp.gamma;
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
    QStringListModel* q = new QStringListModel();
    q->setStringList(QStringList() << "Hammersley" << "Jittered" << "MultiJittered" <<
                            "NRooks" << "PureRandom" << "Regular");
    return q;
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
    QStringListModel* q = new QStringListModel();
    q->setStringList(QStringList() << "AreaLighting" << "MultipleObjects" << "Whitted");
    return q;
  }

  void Api::set_background_color(QColor color) {
    w->set_background_color(RGBColor(color.redF(), color.greenF(), color.blueF()));
  }

  QColor Api::get_background_color() {
    QColor qcolor;
    RGBColor color = w->background_color;
    qcolor.setRgbF(color.r, color.g, color.b);
    return qcolor;
  }

  void Api::render_scene() {
    w->camera_ptr->render_scene(w, get_rendered_image());
  }

  const char* Api::get_rendered_image() {
    return "renderedImage.png";
  }
}
