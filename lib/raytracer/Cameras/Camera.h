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
  void set_eye(const Vector3d&);
  void set_eye(double, double, double);
  void set_lookat(const Vector3d&);
  void set_lookat(double,double,double);
  void set_up_vector(const Vector3d&);
  void set_up_vector(double,double,double);
  void set_exposure_time(double exposure);
  void set_zoom(double zoom);
  void set_view_distance(double d);
  void compute_uvw();
  Vector3d get_eye() const;
  double get_view_distance() const;

protected:
  Vector3d eye;
  Vector3d lookat = Vector3d::Zero();
  Vector3d u, v, w;		// orthonormal basis vectors
  Vector3d up;			// up vector
  double exposure_time = 1.0;
  double zoom = 1.0;      // zoom factor
  double d;         // view plane distance
  Camera& operator= (const Camera& camera);
};


inline void Camera::set_eye(const Vector3d& p) {
  eye = p;
}


inline void Camera::set_eye(double x, double y, double z) {
  eye(0) = x;
  eye(1) = y;
  eye(2) = z;
}


inline void Camera::set_lookat(const Vector3d& p) {
  lookat = p;
}


inline void Camera::set_lookat(double x, double y, double z) {
  lookat(0) = x;
  lookat(1) = y;
  lookat(2) = z;
}


inline void Camera::set_up_vector(const Vector3d& u) {
  up = u;
}


inline void Camera::set_up_vector(double x, double y, double z) {
  up(0) = x;
  up(1) = y;
  up(2) = z;
}


inline void Camera::set_exposure_time(double exposure_time) {
  this->exposure_time = exposure_time;
}


inline Vector3d Camera::get_eye() const {
  return eye;
}


inline double Camera::get_view_distance() const {
  return d;
}


inline void Camera::set_zoom(double zoom) {
  this->zoom = zoom;
}


inline void Camera::set_view_distance(double d) {
  this->d = d;
}

#endif
