#include "Camera.h"

namespace Raytracer {
  Camera::Camera() :
    eye(0.0, 0.0, 250.0),
    u(1.0, 0.0, 0.0),
    v(0.0, 1.0, 0.0),
    w(0.0, 0.0, 1.0),
    up(0.0, 1.0, 0.0)
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


  void Camera::display_pixel(const int row, const int column,
                             const RGBColor& raw_color /**< Pixel color computed by the raytracer */,
                             png::image<png::rgb_pixel>& image,
                             const World* w) const {
    RGBColor mapped_color;
    if (w->vp.out_of_gamut) {
      mapped_color = raw_color.clamp_to_red();
    }
    else {
      mapped_color = raw_color.normalize();
    }
    if (w->vp.gamma != 1.0) {
      mapped_color = mapped_color.powc(1.0 / w->vp.gamma);
    }
    int x = column;
    int y = w->vp.vres - row - 1;
    image[y][x] = png::rgb_pixel(int(mapped_color.r * 255),
                                 int(mapped_color.g * 255),
                                 int(mapped_color.b * 255));
  }
}
