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
  void set_psi_max(const float max);
  void set_lambda_max(const float max);
  void set_horizontal_fov(const float fov);
  void set_vertical_fov(const float fov);
  Vector3d ray_direction(const Vector2d& pixel_point, const int hres, const int vres, const float s) const;
  virtual void render_scene(const World& w, const char* image_file);

 private:
  float psi_max;                // in degrees
  float lambda_max;             // in degrees

};


inline void Spherical::set_psi_max(float _m) {
  psi_max = _m;
}


inline void Spherical::set_lambda_max(float _l) {
  lambda_max = _l;
}


inline void Spherical::set_horizontal_fov(float _v) {
  psi_max = 2 * _v;
}


inline void Spherical::set_vertical_fov(float _v) {
  lambda_max = 2 * _v;
}

#endif
