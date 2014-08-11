#include "Camera.h"

namespace Raytracer {
  Camera::Camera() {
    set_eye_carthesian(Vector3d(100.0, 100.0, 100.0));
    compute_uvw();
  }


  Camera::Camera(const Camera& c) :
    eye_carthesian(c.eye_carthesian),
    eye_spherical(c.eye_spherical),
    lookat(c.lookat),
    u(c.u),
    v(c.v),
    w(c.w),
    up(c.up),
    zoom(c.zoom),
    distance(c.distance)
  {}


  Camera::~Camera() {}


  Camera* Camera::clone() const {
    return new Camera(*this);
  }


  bool Camera::operator==(const Camera& o) const {
    return
      eye_carthesian == o.eye_carthesian &&
      eye_spherical == o.eye_spherical &&
      lookat == o.lookat &&
      zoom == o.zoom &&
      distance == o.distance &&
      up == o.up &&
      u == o.u &&
      v == o.v &&
      w == o.w;
  }


  void Camera::set_eye_spherical_relatively(const double dr, const double dphi, const double dtheta) {
    eye_spherical(0) += dr;
    eye_spherical(1) += dphi;
    eye_spherical(2) += dtheta;
    update_carthesian();
    compute_uvw();
  }


  void Camera::compute_uvw() {
    w = (eye_carthesian - lookat).normalized();
    u = (up.cross(w)).normalized();
    v = w.cross(u);

    /* Take care of the singularity by hardwiring in specific camera orientations. */
    /* Camera looking vertically down. */
    if (eye_carthesian(0) == lookat(0) && eye_carthesian(2) == lookat(2) && eye_carthesian(1) > lookat(1)) {
      u = Vector3d(0.0, 0.0, 1.0);
      v = Vector3d(1.0, 0.0, 0.0);
      w = Vector3d(0.0, 1.0, 0.0);
    }

    /* Camera looking vertically up. */
    if (eye_carthesian(0) == lookat(0) && eye_carthesian(2) == lookat(2) && eye_carthesian(1) < lookat(1)) {
      u = Vector3d(1.0, 0.0, 0.0);
      v = Vector3d(0.0, 0.0, 1.0);
      w = Vector3d(0.0, -1.0, 0.0);
    }
  }


  Vector3d Camera::get_direction(const Vector2d& p) const {
    return ((p(0) * u) + (p(1) * v) - (distance * w)).normalized();
  }


  unsigned Camera::render_scene(const World* w, const char* image_file) {
    /* This should be the first declaration of this function, for
       precision purposes. Beginning of computation. */
    std::clock_t time_begin = clock();
    ViewPlane vp(w->vp);
    png::image< png::rgb_pixel > image(vp.hres, vp.vres);
    Ray ray;
    Vector2d sp;               // sample point in [0,1] x [0,1]
    Vector2d pp;               // sample point on a pixel
    const unsigned number_of_samples = w->sampler_ptr->get_number_of_samples();
    vp.pixel_size /= zoom;
    ray.origin = eye_carthesian;

    for (unsigned r = 0; r < vp.vres; r++) {   // up
      for (unsigned c = 0; c < vp.hres; c++) { // across
        RGBColor  L = RGBColor(0.0, 0.0, 0.0);
        for (unsigned j = 0; j < number_of_samples; ++j) {
          sp = w->sampler_ptr->sample_unit_square();
          pp(0) = vp.pixel_size * (c - 0.5 * vp.hres + sp(0));
          pp(1) = vp.pixel_size * (r - 0.5 * vp.vres + sp(1));
          ray.direction = get_direction(pp);
          L += w->tracer_ptr->trace_ray(ray, 0);
        }
        L /= number_of_samples;
        w->display_pixel(r, c, L, image);
      }
    }
    image.write(image_file);
    /* End of computation. */
    double elapsed_secs = double(clock() - time_begin) / CLOCKS_PER_SEC * 1000;
    return static_cast<unsigned>(elapsed_secs);
  }


  void Camera::update_spherical() {
    /* Carthesian coordinates: c(0) = x, c(1) = y, c(2) = z. */

    /* Radius (r). Between zero and +infinity. */
    eye_spherical(0) = eye_carthesian.norm();

    /* phi */
    eye_spherical(1) = atan2(eye_carthesian(2), eye_carthesian(0)); // y -> z

    /* theta */
    eye_spherical(2) = acos(eye_carthesian(1) / eye_spherical(0)); // z -> y
  }


  void Camera::update_carthesian() {
    /* Spherical coordinates: s(0) = r, s(1) = phi, s(2) = theta. */

    /* x */
    eye_carthesian(0) = eye_spherical(0) * sin(eye_spherical(2)) * cos(eye_spherical(1));

    /* z */
    eye_carthesian(2) = eye_spherical(0) * sin(eye_spherical(2)) * sin(eye_spherical(1)); // c(2) --> c(1)

    /* y */
    eye_carthesian(1) = eye_spherical(0) * cos(eye_spherical(2));  // c(1) --> c(2)
  }
}
