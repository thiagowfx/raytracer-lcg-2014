#include "FishEye.h"

FishEye::FishEye() :
  Camera(),
  psi_max(180.0) // is this a good default value?
{}


FishEye::FishEye(const FishEye& c) :
  Camera(c),
  psi_max(c.psi_max)
{}


Camera* FishEye::clone() const {
  return new FishEye(*this);
}


FishEye& FishEye::operator=(const FishEye& rhs) {
  if (this != &rhs) {
    Camera::operator=(rhs);
    psi_max = rhs.psi_max;
  }

  return *this;
}


FishEye::~FishEye() {}


Vector3d FishEye::ray_direction(const Vector2d&  pp, const int hres, const int vres, const double s, double& r_squared) const {

  /* compute the normalized device coordinates */
  Vector2d pn(2.0 / (s * hres) * pp(0), 2.0 / (s * vres) * pp(1));
  r_squared = pn(0) * pn(0) + pn(1) * pn(1);

  if (r_squared <= 1.0) {
    double r         = sqrt(r_squared);
    double psi       = r * psi_max * PI_ON_180;
    double sin_psi   = sin(psi);
    double cos_psi   = cos(psi);
    double sin_alpha = pn(1) / r;
    double cos_alpha = pn(0) / r;
    Vector3d dir    = sin_psi * cos_alpha * u +  sin_psi * sin_alpha * v - cos_psi * w;
    return dir;
  }
  else
    return Vector3d::Zero();
}


void FishEye::render_scene(const World* w, const char* image_file) {
  RGBColor  L;
  ViewPlane vp(w->vp);
  Ray       ray;
  int       depth = 0;
  Vector2d  sp;        // sample point in [0, 1] X [0, 1]
  Vector2d  pp;        // sample point on the pixel
  double     r_squared; // sum of squares of normalised device coordinates
  const int n     = vp.sampler_ptr->get_num_samples();
  ray.o = eye;

  png::image< png::rgb_pixel > image(vp.hres, vp.vres);

  for (int r = 0; r < vp.vres; r++) {   // up
    for (int c = 0; c < vp.hres; c++) {    // across
      L = RGBColor(0.0, 0.0, 0.0);

      for (int j = 0; j < n; ++j) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp(0) = vp.px_size * (c - 0.5 * vp.hres + sp(0));
        pp(1) = vp.px_size * (r - 0.5 * vp.vres + sp(1));
        ray.d = ray_direction(pp, vp.hres, vp.vres, vp.px_size, r_squared);

        if (r_squared <= 1.0)
          L += w->tracer_ptr->trace_ray(ray, depth);
      }

      L /= n;
      L *= exposure_time;
      w->display_pixel(r, c, L, image);
    }
  }

  image.write(image_file);
}
