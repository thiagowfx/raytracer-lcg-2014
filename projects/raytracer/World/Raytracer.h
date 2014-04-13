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
#include "World.h"

class Raytracer
{
public:
    Raytracer();
    ~Raytracer();
    void set_hres(const int);
    void set_vres(const int);
    void set_number_of_samples(const int);
    void set_pixel_size(double);
    void set_gamma_correction(double);
    void render_scene();
    void set_up();
    const char* image="raytraced_image.png";
private:
    World* w;
    const float ka = 0.25;
    const float kd = 0.75;
    const float ks = 0.12;
    const float expi = 20;
};

#endif // RAYTRACER_H
