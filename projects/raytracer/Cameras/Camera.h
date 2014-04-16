#ifndef __CAMERA__
#define __CAMERA__

/* There is no view plane distance because the fisheye and panoramic cameras don't use it */
#include <Eigen/Dense>
using Eigen::Vector2d;
using Eigen::Vector3d;
class World;  // can't #include "World" here because it contains a camera pointer

class Camera {

public:
  Camera();
  Camera(const Camera& camera);
  virtual Camera* clone() const = 0;
  virtual ~Camera();
  virtual void render_scene(const World* w, const char* image_file) = 0;
  void set_eye(const Vector3d& p);
  void set_lookat(const Vector3d& p);
  void set_up_vector(const Vector3d& u);
  void set_roll(const double ra);
  void set_exposure_time(const double exposure);
  void compute_uvw();
  Vector3d get_eye() const;

protected:
  Vector3d eye;			// eye point
  Vector3d lookat; 		// lookat point
  double ra;			// roll angle
  Vector3d u, v, w;		// orthonormal basis vectors
  Vector3d up;			// up vector
  double	   exposure_time;

  Camera& operator= (const Camera& camera);
};


inline void Camera::set_eye(const Vector3d& p) {
  eye = p;
}


inline void Camera::set_lookat(const Vector3d& p) {
  lookat = p;
}


inline void Camera::set_up_vector(const Vector3d& u) {
  up = u;
}


inline void Camera::set_roll(const double r) {
  ra = r;
}


inline void Camera::set_exposure_time(const double exposure) {
  exposure_time = exposure;
}


inline Vector3d Camera::get_eye() const {
  return eye;
}

#endif
