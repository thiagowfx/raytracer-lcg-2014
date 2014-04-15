#ifndef __SPHERICAL__
#define __SPHERICAL__

#include "Camera.h"
#include "World.h"

class Spherical: public Camera {

 public:
  Spherical();
  Spherical(const Spherical& ph);
  virtual Camera* clone() const;
  Spherical& operator= (const Spherical& rhs);
  virtual ~Spherical();
  void set_psi_max(const double max);
  void set_lambda_max(const double max);
  void set_horizontal_fov(const double fov);
  void set_vertical_fov(const double fov);
  Vector3d ray_direction(const Vector2d& pixel_point, const int hres, const int vres, const double s) const;
  virtual void render_scene(const World* w, const char* image_file);

 private:
  double psi_max;                // in degrees
  double lambda_max;             // in degrees

};


inline void Spherical::set_psi_max(double _m) {
  psi_max = _m;
}


inline void Spherical::set_lambda_max(double _l) {
  lambda_max = _l;
}


inline void Spherical::set_horizontal_fov(double _v) {
  psi_max = 2 * _v;
}


inline void Spherical::set_vertical_fov(double _v) {
  lambda_max = 2 * _v;
}

#endif
