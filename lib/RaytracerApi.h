#ifndef _RAYTRACERAPI_MINE_
#define _RAYTRACERAPI_MINE_

#include "includes.h"

namespace Raytracer {
  class Api {

  public:
    Api();
    ~Api();
    /* ViewPlane */
    void set_hres(int);
    void set_vres(int);
    void set_number_of_samples(int);
    void set_pixel_size(double);
    void set_gamma_correction(double);
    void set_out_of_gamut(bool);
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
    const double dx = 15.0;
  };
}

#endif // _RAYTRACERAPI_MINE_
