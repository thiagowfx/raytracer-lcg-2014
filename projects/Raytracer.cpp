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

/**
 * REMAINDERS:
 * Luzes: parâmetro principal, cor e intensidade.
 */

void Raytracer::set_up() {
  /** Camera */
  Pinhole* camera_ptr = new Pinhole;
  // Orthographic* camera_ptr = new Orthographic;
  cc = Vector3d(0.0, 0.0, 250.0);
  camera_ptr->set_eye(cc);
  camera_ptr->set_lookat(Vector3d::Zero());
  camera_ptr->set_view_distance(250.0);
  camera_ptr->set_zoom(1.0);
  camera_ptr->compute_uvw();
  w->set_camera(camera_ptr);

  PointLight* light_ptr = new PointLight();
  light_ptr->set_location(Vector3d(100.0, 100.0, 200.0));
  light_ptr->scale_radiance(2.0);
  w->add_light(light_ptr);

  Matte* mat1 = new Matte;
  mat1->set_ka(ka);
  mat1->set_kd(kd);
  mat1->set_cd(yellow);
  RaytracerSphere* sphere1 = new RaytracerSphere(Vector3d(250.0, 0.0, 0.0), 30.0);
  sphere1->set_material(mat1);
  sphere1->set_color(yellow);
  w->add_object(sphere1);

  Matte* mat2 = new Matte;
  mat2->set_ka(ka);
  mat2->set_kd(kd);
  mat2->set_cd(white);
  RaytracerSphere*	sphere2 = new RaytracerSphere(Vector3d::Zero(), 15.0);
  sphere2->set_material(mat2);
  sphere2->set_color(white);
  w->add_object(sphere2);

  double dx = 15.0;

  Matte* mat3 = new Matte;
  mat3->set_ka(ka);
  mat3->set_kd(kd);
  mat3->set_cd(light_green);
  RaytracerSphere*	sphere3 = new RaytracerSphere(Vector3d(-2 * dx, 0.0, 0.0), dx);
  sphere3->set_material(mat3);
  w->add_object(sphere3);


  Matte* mat4 = new Matte;
  mat4->set_ka(ka);
  mat4->set_kd(kd);
  mat4->set_cd(dark_green);
  RaytracerSphere*	sphere4 = new RaytracerSphere(Vector3d(2 * dx, 0.0, 0.0), dx);
  sphere4->set_material(mat4);
  w->add_object(sphere4);


  Matte* mat6 = new Matte;
  mat6->set_ka(ka);
  mat6->set_kd(kd);
  mat6->set_cd(light_grey);
  RaytracerSphere*	sphere6 = new RaytracerSphere(Vector3d(0.0, -2 * dx, 0.0), dx);
  sphere6->set_material(mat6);
  w->add_object(sphere6);


  Matte* mat7 = new Matte;
  mat7->set_ka(ka);
  mat7->set_kd(kd);
  mat7->set_cd(grey);
  RaytracerSphere*	sphere7 = new RaytracerSphere(Vector3d(0.0, 2 * dx, 0.0), dx);
  sphere7->set_material(mat7);
  w->add_object(sphere7);

  Matte* mat5 = new Matte;
  mat5->set_ka(ka);
  mat5->set_kd(kd);
  mat5->set_cd(brown);
  Triangle* triangle_ptr5 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
  triangle_ptr5->set_material(mat5);
  // w->add_object(triangle_ptr5);

  Matte* mat8 = new Matte;
  mat8->set_ka(ka);
  mat8->set_kd(kd);
  mat8->set_cd(light_purple);
  RaytracerSphere*	sphere8 = new RaytracerSphere(Vector3d(0.0, 0.0, -2 * dx), dx);
  sphere8->set_material(mat8);
  w->add_object(sphere8);

  Matte* mat9 = new Matte;
  mat9->set_ka(ka);
  mat9->set_kd(kd);
  mat9->set_cd(dark_purple);
  RaytracerSphere*	sphere9 = new RaytracerSphere(Vector3d(0.0, 0.0, 2 * dx), dx);
  sphere9->set_material(mat9);
  w->add_object(sphere9);
}

void Raytracer::set_up_testing() {
  /** Camera */
  Pinhole* camera_ptr = new Pinhole;
  cc = Vector3d(250.0, 0.0, 250.0);
  camera_ptr->set_eye(cc);
  camera_ptr->set_lookat(Vector3d::Zero());
  camera_ptr->set_view_distance(250.0);
  camera_ptr->compute_uvw();
  w->set_camera(camera_ptr);

  /** Luzes */
  Directional* dir1 = new Directional();
  dir1->set_direction(cc);
  dir1->scale_radiance(1.0);
  dir1->set_color(white);

  Matte* mat1 = new Matte;
  mat1->set_cd(blue);
  mat1->set_ka(ka);
  mat1->set_kd(kd);
  RaytracerPlane* plan_xy = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 0.0, 1.0));
  plan_xy->set_material(mat1);
  w->add_object(plan_xy);

  Matte* mat2 = new Matte;
  mat2->set_cd(green);
  mat2->set_ka(ka);
  mat2->set_kd(kd);
  RaytracerPlane* plan_yz = new RaytracerPlane(Vector3d::Zero(), Vector3d(1.0, 0.0, 0.0));
  plan_yz->set_material(mat2);
  w->add_object(plan_yz);

  Matte* mat3 = new Matte;
  mat3->set_cd(red);
  mat3->set_ka(ka);
  mat3->set_kd(kd);
  RaytracerPlane* plan_xz = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
  plan_xz->set_material(mat3);
  w->add_object(plan_xz);
}
