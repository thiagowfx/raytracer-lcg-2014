#include "Raytracer.h"

Raytracer::Raytracer() :
  w(new World)
{
  set_up();
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
    std::cout << "No tracer set" << std::endl;
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
  sprintf(str, "Eye(abs): (%.2lf, %.2lf, %.2lf)", v(0), v(1), v(2));
  return str;
}

const char* Raytracer::get_camera_eye_cylindrical_as_string() {
  static char str[50];
  sprintf(str, "Eye(cyl): (%.2lf, %.2lf, %.2lf)", cc(0), cc(1), cc(2));
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
  cc(1) = clamp(cc(1) + dphi, 4 * M_PI);
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

void Raytracer::set_up() {

  /* Camera */
  Pinhole* camera_ptr = new Pinhole;
  // Orthographic* camera_ptr = new Orthographic;
  cc = Vector3d(0.0, 0.0, 500.0);
  camera_ptr->set_eye(cc);
  camera_ptr->set_lookat(Vector3d::Zero());
  camera_ptr->set_view_distance(250.0);
  camera_ptr->set_zoom(1.0);
  camera_ptr->compute_uvw();
  w->set_camera(camera_ptr);

  PointLight* light_ptr = new PointLight();
  light_ptr->set_location(Vector3d(100, 100, 200));
  light_ptr->scale_radiance(2.0);
  w->add_light(light_ptr);

  Matte* matte_ptr = new Matte;
  matte_ptr->set_ka(0.2);
  matte_ptr->set_kd(0.8);
  matte_ptr->set_cd(RGBColor(0.9, 0.9, 0.2));				// yellow
  RaytracerSphere*	sphere_ptr = new RaytracerSphere(Vector3d(250.0, 0.0, 0.0), 30.0);
  sphere_ptr->set_material(matte_ptr);
  sphere_ptr->set_color(RGBColor(0.9, 0.9, 0.2));
  w->add_object(sphere_ptr);

  Matte* matte_ptr3 = new Matte;
  matte_ptr3->set_ka(0.2);
  matte_ptr3->set_kd(0.8);
  matte_ptr3->set_cd(orange);
  RaytracerSphere*	sphere_ptr3 = new RaytracerSphere(Vector3d::Zero(), 15.0);
  sphere_ptr3->set_material(matte_ptr3);
  sphere_ptr3->set_color(orange);
  w->add_object(sphere_ptr3);

  Matte* matte_ptr2 = new Matte;
  matte_ptr2->set_ka(ka);
  matte_ptr2->set_kd(kd);
  matte_ptr2->set_cd(RGBColor(0.2, 0.9, 0.2));
  Triangle* triangle_ptr1 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
  triangle_ptr1->set_material(matte_ptr2);
  triangle_ptr1->set_color(RGBColor(0.2, 0.9, 0.2));
  w->add_object(triangle_ptr1);
}
