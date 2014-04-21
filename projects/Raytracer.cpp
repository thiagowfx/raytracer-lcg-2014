#include "Raytracer.h"

Raytracer::Raytracer() :
  w(new World)
{
  set_up();
  // set_up_testing();
}

Raytracer::~Raytracer() {
  delete w;
}

void Raytracer::set_hres(int resolution) {
  w->vp.set_hres(resolution);
}

void Raytracer::set_vres(int resolution) {
  w->vp.set_vres(resolution);
}

void Raytracer::set_number_of_samples(int samples) {
  w->vp.set_samples(samples);
}

void Raytracer::set_pixel_size(double size) {
  w->vp.set_pixel_size(size);
}

void Raytracer::set_gamma_correction(double gamma) {
  w->vp.set_gamma(gamma);
}

void Raytracer::set_show_out_of_gamut(bool b) {
  w->vp.set_show_of_gamut(b);
}


void Raytracer::set_background_color(QColor c) {
  w->background_color = RGBColor(c.redF(), c.greenF(), c.blueF());
}

void Raytracer::set_ambient_light_color(QColor c) {
  w->ambient_ptr->set_color(RGBColor(c.redF(), c.greenF(), c.blueF()));
}

void Raytracer::set_tracer(Tracer* tracer) {
  w->tracer_ptr = tracer;
}

void Raytracer::set_tracer(QString s) {
  if (s == QString("RayCast"))
    set_tracer(new RayCast(w));
  else if (s == QString("Whitted"))
    set_tracer(new Whitted(w));
  else if (s == QString("MultipleObjects"))
    set_tracer(new MultipleObjects(w));
  else {
    std::cout << "ERROR: No tracer set" << std::endl;
    exit(1);
  }
}

void Raytracer::set_ambient_radiance(double r) {
  w->ambient_ptr->scale_radiance(r);
}

void Raytracer::change_view_distance(double dd) {
  set_view_distance(w->camera_ptr->get_view_distance() + dd);
}

void Raytracer::set_view_distance(double d) {
  w->camera_ptr->set_view_distance(d);
}

void Raytracer::set_camera_zoom(double z) {
  w->camera_ptr->set_zoom(z);
}

const char* Raytracer::get_camera_eye_as_string() {
  static char str[50];
  Vector3d v = w->camera_ptr->get_eye();
  sprintf(str, "(x = %.2lf, y = %.2lf, z = %.2lf)", v(0), v(1), v(2));
  return str;
}

const char* Raytracer::get_camera_eye_cylindrical_as_string() {
  static char str[50];
  sprintf(str, "C: (p = %.2lf, phi = %.1lfº, z = %.2lf)", cc(0), cc(1) * (180.0/ M_PI), cc(2));
  return str;
}

void Raytracer::move_camera_eye_absolute(Vector3d v) {
  w->camera_ptr->set_eye(v);
  w->camera_ptr->compute_uvw();
}

void Raytracer::move_camera_eye_absolute(double x, double y, double z) {
  move_camera_eye_absolute(Vector3d(x, y, z));
}

void Raytracer::move_camera_eye_relative(double dx, double dy, double dz) {
  Vector3d v = w->camera_ptr->get_eye();
  move_camera_eye_absolute(v(0) + dx, v(1) + dy, v(2) + dz);
}

void Raytracer::move_camera_eye_absolute_cylindrical(double p, double phi, double z) {
  cc = Vector3d(p, phi, z);
  move_camera_eye_absolute(cylindrical_to_absolute(cc));
}

void Raytracer::move_camera_eye_relative_cylindrical(double dp, double dphi, double dz) {
  cc(0) += dp;
  cc(1) = clamp(cc(1) + dphi, 2 * M_PI);
  cc(2) += dz;
  move_camera_eye_absolute(cylindrical_to_absolute(cc));
}

Vector3d Raytracer::cylindrical_to_absolute(Vector3d c) {
  Vector3d a;
  a(0) = c(0) * cos(c(1));
  a(1) = c(0) * sin(c(1));
  a(2) = c(2);
  return a;
}

inline double Raytracer::clamp(double x, double max) {
  return x - int(x / max) * max;
}

void Raytracer::render_scene() {
  w->camera_ptr->render_scene(w, image);
}

void Raytracer::set_up_camera() {
  Pinhole* camera_ptr = new Pinhole();
  // Orthographic* camera_ptr = new Orthographic();

  cc = Vector3d(250.0, 0.0, 250.0);
  camera_ptr->set_eye(cc);
  camera_ptr->set_lookat(Vector3d::Zero());
  camera_ptr->compute_uvw();
  w->set_camera(camera_ptr);
}

/**
 * REMAINDERS:
 * Luzes: parâmetro principal, cor e intensidade.
 */

void Raytracer::set_up() {
  set_up_camera();

  PointLight* light_ptr = new PointLight();
  light_ptr->set_location(Vector3d(100.0, 100.0, 200.0));
  light_ptr->scale_radiance(2.0);
  w->add_light(light_ptr);

  RaytracerSphere* sphere1 = new RaytracerSphere(Vector3d(250.0, 0.0, 0.0), 30.0);
  sphere1->set_material(Matte::dummy(light_green));
  w->add_object(sphere1);

  RaytracerSphere*	sphere2 = new RaytracerSphere(Vector3d::Zero(), 15.0);
  sphere2->set_material(Matte::dummy(white));
  w->add_object(sphere2);

  RaytracerSphere*	sphere3 = new RaytracerSphere(Vector3d(-2 * dx, 0.0, 0.0), dx);
  sphere3->set_material(Matte::dummy(light_green));
  w->add_object(sphere3);

  RaytracerSphere*	sphere4 = new RaytracerSphere(Vector3d(2 * dx, 0.0, 0.0), dx);
  sphere4->set_material(Matte::dummy(dark_green));
  w->add_object(sphere4);

  RaytracerSphere*	sphere6 = new RaytracerSphere(Vector3d(0.0, -2 * dx, 0.0), dx);
  sphere6->set_material(Matte::dummy(light_grey));
  w->add_object(sphere6);


  RaytracerSphere*	sphere7 = new RaytracerSphere(Vector3d(0.0, 2 * dx, 0.0), dx);
  sphere7->set_material(Matte::dummy(grey));
  w->add_object(sphere7);

  Triangle* triangle_ptr5 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
  triangle_ptr5->set_material(Matte::dummy(brown));
  w->add_object(triangle_ptr5);

  RaytracerSphere*	sphere8 = new RaytracerSphere(Vector3d(0.0, 0.0, -2 * dx), dx);
  sphere8->set_material(Matte::dummy(light_purple));
  w->add_object(sphere8);

  RaytracerSphere*	sphere9 = new RaytracerSphere(Vector3d(0.0, 0.0, 2 * dx), dx);
  sphere9->set_material(Matte::dummy(dark_purple));
  w->add_object(sphere9);
}

void Raytracer::set_up_testing() {
  set_up_camera();

  /** Luzes */
  Directional* dir1 = new Directional();
  dir1->set_direction(cc);
  dir1->scale_radiance(1.0);
  dir1->set_color(white);

  RaytracerPlane* plan_xy = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 0.0, 1.0));
  plan_xy->set_material(Matte::dummy(blue));
  w->add_object(plan_xy);

  RaytracerPlane* plan_yz = new RaytracerPlane(Vector3d::Zero(), Vector3d(1.0, 0.0, 0.0));
  plan_yz->set_material(Matte::dummy(green));
  w->add_object(plan_yz);

  RaytracerPlane* plan_xz = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
  plan_xz->set_material(Matte::dummy(red));
  w->add_object(plan_xz);
}
