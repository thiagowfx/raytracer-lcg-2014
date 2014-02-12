#ifndef __CAMERA__
#define __CAMERA__

// This file contains the declaration of the base class Camera
// There is no view plane distance because the fisheye and panoramic cameras don't use it

#include <Eigen/Dense>

using Eigen::Vector3d;

class World;  // can't #include "World" here because World contains a camera pointer

class Camera {
 public:
	
  Camera();                              // default constructor
  Camera(const Camera& camera);          // ncopy constructor
  virtual Camera* clone(void) const = 0; // virtual copy constructor
  virtual ~Camera();   							
  virtual void render_scene(const World& w) = 0;
  void set_eye(const Vector3d& p);
  void set_eye(const float x, const float y, const float z);
  void set_lookat(const Vector3d& p);
  void set_lookat(const float x, const float y, const float z);
  void set_up_vector(const Vector3d& u);
  void set_up_vector(const float x, const float y, const float z);
  void set_roll(const float ra);
  void set_exposure_time(const float exposure);
  void compute_uvw(void);
		
 protected:		
	
  Vector3d eye;			// eye point
  Vector3d lookat; 		// lookat point
  float	   ra;			// roll angle
  Vector3d u, v, w;		// orthonormal basis vectors
  Vector3d up;			// up vector
  float	   exposure_time;
		
  Camera& operator= (const Camera& camera);
};


inline void Camera::set_eye(const Vector3d& p) {
  eye = p;
}


inline void Camera::set_eye(const float x, const float y, const float z) {
  eye(0) = x;
  eye(1) = y;
  eye(2) = z;
}


inline void Camera::set_lookat(const Vector3d& p) {
  lookat = p;
}


inline void Camera::set_lookat(const float x, const float y, const float z) {
  lookat(0) = x;
  lookat(1) = y;
  lookat(2) = z;
}


inline void Camera::set_up_vector(const Vector3d& u) {
  up = u;
}


inline void Camera::set_up_vector(const float x, const float y, const float z) {
  up(0) = x;
  up(1) = y;
  up(2) = z;
}


inline void Camera::set_roll(const float r) { 
  ra = r;
}


inline void Camera::set_exposure_time(const float exposure) {
  exposure_time = exposure;
}

#endif
