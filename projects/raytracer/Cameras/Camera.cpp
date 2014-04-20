#include "Camera.h"

Camera::Camera() :
  eye(0.0, 0.0, 500.0),
  lookat(Vector3d::Zero()),
  u(1.0, 0.0, 0.0),
  v(0.0, 1.0, 0.0),
  w(0.0, 0.0, 1.0),
  up(0.0, 1.0, 0.0),
  exposure_time(1.0),
  zoom(1.0),
  d(250.0)
{}


Camera::Camera(const Camera& c) :
  eye(c.eye),
  lookat(c.lookat),
  u(c.u),
  v(c.v),
  w(c.w),
  up(c.up),
  exposure_time(c.exposure_time),
  zoom(c.zoom),
  d(c.d)
{}


Camera& Camera::operator= (const Camera& rhs) {
  if (this != &rhs) {
    eye           = rhs.eye;
    lookat        = rhs.lookat;
    up            = rhs.up;
    u             = rhs.u;
    v             = rhs.v;
    w             = rhs.w;
    exposure_time = rhs.exposure_time;
    zoom          = rhs.zoom;
    d             = rhs.d;
  }
  return *this;
}


Camera::~Camera() {}


/* This computes an orthornormal basis given the view point, lookat point, and up vector */
void Camera::compute_uvw() {
  w = eye - lookat;
  w.normalize();
  u = up.cross(w);
  u.normalize();
  v = w.cross(u);

  /* take care of the singularity by hardwiring in specific camera orientations */
  /* camera looking vertically down */
  if (eye(0) == lookat(0) && eye(2) == lookat(2) && eye(1) > lookat(1)) {
    u = Vector3d(0.0, 0.0, 1.0);
    v = Vector3d(1.0, 0.0, 0.0);
    w = Vector3d(0.0, 1.0, 0.0);	
  }

  /* camera looking vertically up */
  if (eye(0) == lookat(0) && eye(2) == lookat(2) && eye(1) < lookat(1)) {
    u = Vector3d(1.0, 0.0, 0.0);
    v = Vector3d(0.0, 0.0, 1.0);
    w = Vector3d(0.0, -1.0, 0.0);
  }
}
