#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ambient.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "Camera.h"
#include "Directional.h"
#include "Emissive.h"
#include "GeometricObject.h"
#include "Jittered.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "MultiJittered.h"
#include "MultipleObjects.h"
#include "Orthographic.h"
#include "Phong.h"
#include "Pinhole.h"
#include "PointLight.h"
#include "PrimitivaDaniel.h"
#include "RGBColor.h"
#include "Ray.h"
#include "Raytracer.h"
#include "RaytracerPlane.h"
#include "RaytracerSphere.h"
#include "Rectangle.h"
#include "Reflective.h"
#include "Regular.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "Whitted.h"
#include "World.h"

#include "pc-shape-detection.h"

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
  void set_max_depth(int);
  /* World */
  void set_background_color(QColor);
  void set_tracer(Tracer*);
  void set_tracer(QString);
  void set_ambient_light(Ambient*);
  /* Camera */
  void change_view_distance(double);
  void set_view_distance(double);
  void set_camera_zoom(double);
  const char* get_camera_eye_as_string();
  const char* get_camera_eye_cylindrical_as_string();
  const char* get_camera_eye_spherical_as_string();
  void camera_eye_absolute(Vector3d);
  void camera_eye_absolute(double,double,double);
  void camera_eye_relative(double,double,double);
  void camera_eye_relative_cylindrical(double,double,double);
  void camera_eye_relative_spherical(double,double,double);
  /* Utilities*/
  Vector3d cylindrical_to_absolute(Vector3d);
  Vector3d absolute_to_cylindrical(Vector3d);
  Vector3d spherical_to_absolute(Vector3d);
  Vector3d absolute_to_spherical(Vector3d);
  double clamp(double x, double max); /** ASSUME: max > 0. Return [0, max) */
  /* Raytracer */
  void render_scene();
  void set_up_camera();
  void set_up_axis_matte();
  void set_up_axis_phong();
  const char* image="raytraced_image.png";
private:
  World* w;
  const double ks = 0.12; /** valor para constante especular */
  const double expi = 10.0; /** expoente para reflexão especular */
  const double dx = 15.0;
};

#endif // RAYTRACER_H
