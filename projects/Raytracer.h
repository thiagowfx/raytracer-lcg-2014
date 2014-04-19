#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ambient.h"
#include "Camera.h"
#include "Constants.h"
#include "Directional.h"
#include "FishEye.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "MultipleObjects.h"
#include "Orthographic.h"
#include "Phong.h"
#include "Pinhole.h"
#include "PointLight.h"
#include "PrimitivaDaniel.h"
#include "RGBColor.h"
#include "Randomness.h"
#include "Ray.h"
#include "RayCast.h"
#include "Raytracer.h"
#include "RaytracerPlane.h"
#include "RaytracerSphere.h"
#include "Reflective.h"
#include "Regular.h"
#include "ShadeRec.h"
#include "Spherical.h"
#include "Tracer.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "Whitted.h"
#include "World.h"

#include <cstdio>
#include <cmath>
#include <QColor>
#include <QString>

class Raytracer {

public:
    Raytracer();
    ~Raytracer();
    /* ViewPlane */
    void set_hres(int);
    void set_vres(int);
    void set_number_of_samples(int);
    void set_pixel_size(double);
    void set_gamma_correction(double);
    void set_show_out_of_gamut(bool);
    /* World */
    void set_background_color(QColor);
    void set_ambient_light_color(QColor);
    void set_tracer(Tracer*);
    void set_tracer(QString);
    /* Ambient Light */
    void set_ambient_radiance(double);
    /* Camera */
    const char* get_camera_eye_as_string();
    const char* get_camera_eye_spherical_as_string();
    void move_camera_eye_absolute(Vector3d);
    void move_camera_eye_absolute(double,double,double);
    void move_camera_eye_relative(double,double,double);
    void move_camera_eye_absolute_spherical(double,double,double);
    void move_camera_eye_relative_spherical(double,double,double);
    /* Utilities*/
    Vector3d spherical_to_absolute(Vector3d);
    Vector3d absolute_to_spherical(Vector3d);
    /** ASSUME: max > 0. Return [0, max) */
    double clamp(double x, double max);
    /* Raytracer */
    void render_scene();
    void set_up();
    const char* image="raytraced_image.png";
private:
    World* w;
    Vector3d sc; /** spherical coordinates: r (pho), phi (azimuthal), theta (inclination) */
    const double ka = 0.2;
    const double kd = 0.8;
    const double ks = 0.12;
    const double expi = 20;
};

#endif // RAYTRACER_H
