#include "Raytracer.h"

Raytracer::Raytracer() :
    w(new World)
{
    set_up();
}

Raytracer::~Raytracer() {
    delete w;
}

void Raytracer::set_hres(const int resolution) {
    w->vp.set_hres(resolution);
}

void Raytracer::set_vres(const int resolution) {
    w->vp.set_vres(resolution);
}

void Raytracer::set_number_of_samples(const int samples) {
    w->vp.set_samples(samples);
}

void Raytracer::set_pixel_size(double size) {
    w->vp.set_pixel_size(size);
}

void Raytracer::set_gamma_correction(double gamma) {
    w->vp.set_gamma(gamma);
}

void Raytracer::render_scene() {
    puts("INFO: BEGIN Raytracer::render_scene()");
    w->camera_ptr->render_scene(w, image);
    puts("INFO: END Raytracer::render_scene()");
}

void Raytracer::set_up() {
    w->background_color = green;
    w->vp.set_pixel_size(1.0);
    w->vp.set_samples(4);

    w->tracer_ptr = new RayCast(w);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(Vector3d(0, 0, 250));
    camera_ptr->set_lookat(Vector3d::Zero());
    camera_ptr->set_view_distance(200);
    camera_ptr->compute_uvw();
    w->set_camera(camera_ptr);

    Phong*    phong_ptr2 = new Phong;
    phong_ptr2->set_ka(0.25);
    phong_ptr2->set_kd(0.5);
    phong_ptr2->set_cd(red);
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
