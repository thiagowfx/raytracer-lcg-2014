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

void Raytracer::set_background_color(double r, double g, double b) {
    w->background_color = RGBColor(r, g, b);
}

void Raytracer::set_ambient_radiance(double r) {
    w->ambient_ptr->scale_radiance(r);
}

const char* Raytracer::get_camera_eye_as_string() {
    static char str[50];
    Vector3d v = w->camera_ptr->get_eye();
    sprintf(str, "Eye: (%.2lf, %.2lf, %.2lf)", v(0), v(1), v(2));
    return str;
}

void Raytracer::move_camera_eye_relative(double x, double y, double z) {
    Vector3d v = w->camera_ptr->get_eye();
    w->camera_ptr->set_eye(Vector3d(v(0) + x, v(1) + y, v(2) + z));
}

void Raytracer::render_scene() {
    w->camera_ptr->render_scene(w, image);
}

void Raytracer::set_up() {
    w->tracer_ptr = new RayCast(w);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(Vector3d(0, 0, 250));
    camera_ptr->set_lookat(Vector3d::Zero());
    camera_ptr->set_view_distance(200);
    camera_ptr->compute_uvw();
    w->set_camera(camera_ptr);

    Phong* phong_ptr2 = new Phong;
    phong_ptr2->set_ka(0.25);
    phong_ptr2->set_kd(0.5);
    phong_ptr2->set_cd(yellow);
    phong_ptr2->set_ks(0.05);
    phong_ptr2->set_exp(50);

    Triangle* triangle_ptr1 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
    triangle_ptr1->set_material(phong_ptr2);
    w->add_object(triangle_ptr1);

    if (w->tracer_ptr == NULL) {
      puts("ERROR: No world tracer set.");
      exit(1);
    }
}
