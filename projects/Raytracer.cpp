#include "Raytracer.h"

Raytracer::Raytracer() :
    w(new World)
{
    set_up_camera();

    /** Only uncomment one */
    // set_up_axis_matte();
    set_up_axis_phong();
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
    Vector3d cc = absolute_to_cylindrical(w->camera_ptr->get_eye());
    sprintf(str, "C: (p = %.2lf, phi = %.1lfº, z = %.2lf)", cc(0), cc(1) * (180.0/ M_PI), cc(2));
    return str;
}

const char* Raytracer::get_camera_eye_spherical_as_string() {
    static char str[50];
    Vector3d ss = absolute_to_spherical(w->camera_ptr->get_eye());
    sprintf(str, "C: (p = %.2lf, phi = %.1lf graus, z = %.2lf graus)", ss(0), ss(1) * (180.0/ M_PI), ss(2) * (180.0 / M_PI) );
    return str;
}

void Raytracer::camera_eye_absolute(Vector3d v) {
    w->camera_ptr->set_eye(v);
    w->camera_ptr->compute_uvw();
}

void Raytracer::camera_eye_absolute(double x, double y, double z) {
    camera_eye_absolute(Vector3d(x, y, z));
}

void Raytracer::camera_eye_relative(double dx, double dy, double dz) {
    Vector3d v = w->camera_ptr->get_eye();
    camera_eye_absolute(v(0) + dx, v(1) + dy, v(2) + dz);
}

void Raytracer::camera_eye_relative_cylindrical(double dp, double dphi, double dz) {
    Vector3d cc = absolute_to_cylindrical(w->camera_ptr->get_eye());
    cc(0) += dp;
    cc(1) = clamp(cc(1) + dphi, 2 * M_PI);
    cc(2) += dz;
    camera_eye_absolute(cylindrical_to_absolute(cc));
}

void Raytracer::camera_eye_relative_spherical(double dr, double dphi, double dtheta) {
    Vector3d ss = absolute_to_spherical(w->camera_ptr->get_eye());
    ss(0) += dr;
    ss(1) = ss(1) + dphi;
    ss(2) = ss(2) + dtheta;
    camera_eye_absolute(spherical_to_absolute(ss));
}

Vector3d Raytracer::cylindrical_to_absolute(Vector3d c) {
    Vector3d a;
    a(0) = c(0) * cos(c(1));
    a(1) = c(0) * sin(c(1));
    a(2) = c(2);
    return a;
}

Vector3d Raytracer::absolute_to_cylindrical(Vector3d a) {
    Vector3d c;
    c(0) = sqrt(a(0) * a(0) + a(1) * a(1));
    c(1) = atan2(a(1), a(0));
    c(2) = a(2);
    return c;
}

Vector3d Raytracer::spherical_to_absolute(Vector3d s) {
    Vector3d a;
    // s(0) = r
    // s(1) = phi
    // s(2) = theta
    // a(0) = x, a(1) = y, a(2) = z
    a(0) = s(0) * sin(s(2)) * cos(s(1));
    a(2) = s(0) * sin(s(2)) * sin(s(1)); // --> a(2) --> a(1)
    a(1) = s(0) * cos(s(2));  // a(1) --> a(2)
    return a;
}

Vector3d Raytracer::absolute_to_spherical(Vector3d a) {
    // s(0) = r
    // s(1) = phi
    // s(2) = theta
    // a(0) = x, a(1) = y, a(2) = z
    Vector3d s;
    s(0) = a.norm();
    s(1) = atan2(a(2), a(0)); // y -> z
    s(2) = acos(a(1) / s(0)); // z ->y
    return s;
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

    camera_ptr->set_eye(Vector3d(250.0, 0.0, 250.0));
    camera_ptr->set_lookat(Vector3d::Zero());
    camera_ptr->compute_uvw();
    w->set_camera(camera_ptr);
}

/**
 * REMAINDERS:
 * Luzes: parâmetro principal, cor e intensidade.
 */

void Raytracer::set_up_axis_matte() {
    PointLight* light_ptr = new PointLight();
    light_ptr->set_location(w->camera_ptr->get_eye());
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

    /*
    Triangle* triangle_ptr5 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
    triangle_ptr5->set_material(Matte::dummy(brown));
    w->add_object(triangle_ptr5);
    */

    RaytracerSphere*	sphere8 = new RaytracerSphere(Vector3d(0.0, 0.0, -2 * dx), dx);
    sphere8->set_material(Matte::dummy(light_purple));
    w->add_object(sphere8);

    RaytracerSphere*	sphere9 = new RaytracerSphere(Vector3d(0.0, 0.0, 2 * dx), dx);
    sphere9->set_material(Matte::dummy(dark_purple));
    w->add_object(sphere9);

    RaytracerPlane* plane0 = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
    plane0->set_material(Matte::dummy(light_gray));
    w->add_object(plane0);

    vector<PrimitivaDaniel*> pds = PrimitivaDaniel::dummy("/home/thiago/workbench/RaytracerProject/projects/pcs-detection/pcs-detection/SHAPES2");
    for (unsigned i = 0; i < pds.size(); ++i) {
      pds[i]->set_material(Matte::dummy(yellow));
      w->add_object(pds[i]);
    }
}

void Raytracer::set_up_axis_phong() {
    PointLight* light_ptr = new PointLight();
    light_ptr->set_location(w->camera_ptr->get_eye());
    light_ptr->scale_radiance(2.0);
    light_ptr->set_shadows(false);
    w->add_light(light_ptr);

    w->set_ambient_light(new AmbientOccluder);

    RaytracerSphere* sphere1 = new RaytracerSphere(Vector3d(250.0, 0.0, 0.0), 30.0);
    sphere1->set_material(Phong::dummy(light_green));
    w->add_object(sphere1);

    RaytracerSphere* sphere2 = new RaytracerSphere(Vector3d::Zero(), 15.0);
    sphere2->set_material(Phong::dummy(white));
    sphere2->set_shadows(false);
    w->add_object(sphere2);

    RaytracerSphere*	sphere3 = new RaytracerSphere(Vector3d(-2 * dx, 0.0, 0.0), dx);
    sphere3->set_material(Phong::dummy(light_green));
    w->add_object(sphere3);

    RaytracerSphere*	sphere4 = new RaytracerSphere(Vector3d(2 * dx, 0.0, 0.0), dx);
    sphere4->set_material(Phong::dummy(dark_green));
    w->add_object(sphere4);

    RaytracerSphere*	sphere6 = new RaytracerSphere(Vector3d(0.0, -2 * dx, 0.0), dx);
    sphere6->set_material(Phong::dummy(light_grey));
    w->add_object(sphere6);

    RaytracerSphere*	sphere7 = new RaytracerSphere(Vector3d(0.0, 2 * dx, 0.0), dx);
    sphere7->set_material(Phong::dummy(grey));
    w->add_object(sphere7);

    Triangle* triangle5 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
    triangle5->set_material(Phong::dummy(brown));
    w->add_object(triangle5);

    RaytracerSphere*	sphere8 = new RaytracerSphere(Vector3d(0.0, 0.0, -2 * dx), dx);
    sphere8->set_material(Phong::dummy(light_purple));
    w->add_object(sphere8);

    RaytracerSphere*	sphere9 = new RaytracerSphere(Vector3d(0.0, 0.0, 2 * dx), dx);
    sphere9->set_material(Phong::dummy(dark_purple));
    w->add_object(sphere9);

    RaytracerPlane* plane0 = new RaytracerPlane(Vector3d::Zero(), Vector3d(0.0, 1.0, 0.0));
    plane0->set_material(Phong::dummy(light_gray));
    w->add_object(plane0);
}
