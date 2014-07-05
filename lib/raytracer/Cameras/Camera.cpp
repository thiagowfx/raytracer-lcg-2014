#include "Camera.h"

namespace Raytracer {
  Camera::Camera() {
    compute_uvw();
  }


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


  Camera::~Camera() {}


  /* This computes an orthornormal basis given the eye, lookat point, and up vector */
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
}
