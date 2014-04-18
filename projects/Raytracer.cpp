#include "Raytracer.h"

Raytracer::Raytracer() :
    w(new World),
    sc(250.0, 0.0, M_PI / 2.0)
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

void Raytracer::set_background_color(double r, double g, double b) {
    w->background_color = RGBColor(r, g, b);
}

void Raytracer::set_tracer(Tracer* tracer) {
    w->tracer_ptr = tracer;
}

void Raytracer::set_tracer(QString s) {
    if (s == QString("RayCast"))
        w->tracer_ptr = new RayCast(w);
    else if (s == QString("Whitted"))
        w->tracer_ptr = new Whitted(w);
    else if (s == QString("MultipleObjects"))
        w->tracer_ptr=  new MultipleObjects(w);
}

void Raytracer::set_ambient_radiance(double r) {
    w->ambient_ptr->scale_radiance(r);
}

const char* Raytracer::get_camera_eye_as_string() {
    static char str[50];
    Vector3d v = w->camera_ptr->get_eye();
    sprintf(str, "Eye(abs): (%.2lf, %.2lf, %.2lf)", v(0), v(1), v(2));
    return str;
}

const char *Raytracer::get_camera_eye_spherical_as_string() {
    static char str[50];
    sprintf(str, "Eye(sph): (%.2lf, %.2lf, %.2lf)", sc(0), sc(1), sc(2));
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

void Raytracer::move_camera_eye_absolute_spherical(double r, double phi, double theta) {
    sc = Vector3d(r, phi, theta);
    move_camera_eye_absolute(spherical_to_absolute(sc));
}

void Raytracer::move_camera_eye_relative_spherical(double dr, double dphi, double dtheta) {
    sc(0) = sc(0) + dr;
    sc(1) = clamp(sc(1) + dphi, 2 * M_PI);
    sc(2) = clamp(sc(2) + dtheta, 2 * M_PI);
    move_camera_eye_absolute(spherical_to_absolute(sc));
}

inline Vector3d Raytracer::spherical_to_absolute(Vector3d s) {
    Vector3d a;
    a(0) = s(0) * cos(s(1)) * sin(s(2));
    a(1) = s(0) * sin(s(1)) * sin(s(2));
    a(2) = s(0) * cos(s(2));
    return a;
}

inline Vector3d Raytracer::absolute_to_spherical(Vector3d a) {
    Vector3d s;
    s(0) = a.norm();
    s(1) = atan2(a(1), a(0));
    s(2) = acos(a(2) / s(0));
    return s;
}

inline double Raytracer::clamp(double x, double max) {
    return x - int(x / max) * max;
}

void Raytracer::render_scene() {
    w->camera_ptr->render_scene(w, image);
}

void Raytracer::set_up() {
    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(Vector3d(0, 0, 250));
    camera_ptr->set_lookat(Vector3d::Zero());
    camera_ptr->set_view_distance(200);
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

    RaytracerSphere*	sphere_ptr = new RaytracerSphere(Vector3d::Zero(), 30.0);
    sphere_ptr->set_material(matte_ptr);
    sphere_ptr->set_color(RGBColor(0.9, 0.9, 0.2));
    w->add_object(sphere_ptr);

    Matte* matte_ptr2 = new Matte;
    matte_ptr2->set_ka(ka);
    matte_ptr2->set_kd(kd);
    matte_ptr2->set_cd(RGBColor(0.2, 0.9, 0.2));

    Triangle* triangle_ptr1 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
    triangle_ptr1->set_material(matte_ptr2);
    triangle_ptr1->set_color(RGBColor(0.2, 0.9, 0.2));
    w->add_object(triangle_ptr1);
}
