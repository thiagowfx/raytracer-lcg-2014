#ifndef __FISHEYE__
#define __FISHEYE__

#include "Camera.h"
#include "World.h"


class FishEye: public Camera {

 public:
  FishEye();
  FishEye(const FishEye& ph);
  virtual Camera* clone() const;
  FishEye& operator= (const FishEye& rhs);
  virtual ~FishEye();
  void set_psi_max(const float max);
  void set_fov(const float fov);
  Vector3d ray_direction(const Vector2d& pixel_point, const int hres, const int vres, const float s, float& r_squared) const;
  virtual void render_scene(const World& w, FILE *fp);

 private:
  float psi_max;          // in degrees
  
};


inline void FishEye::set_psi_max(float _m) {
  psi_max = _m;
}

inline void FishEye::set_fov(float _f) {
  psi_max = 2 * _f; // this right? check page 187 later
}

#endif
