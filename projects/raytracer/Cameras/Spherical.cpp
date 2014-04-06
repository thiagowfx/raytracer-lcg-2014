#include "Spherical.h"

Spherical::Spherical() :
  Camera(),
  psi_max(180.0),               // are these good default values?
  lambda_max(60.0)
{}


Spherical::Spherical(const Spherical& c) :
  Camera(c),
  psi_max(c.psi_max)
{}


Camera* Spherical::clone() const {
  return new Spherical(*this);
}


Spherical& Spherical::operator=(const Spherical& rhs) {
  if (this != &rhs) {
    Camera::operator=(rhs);
    psi_max = rhs.psi_max;
  }

  return *this;
}


Spherical::~Spherical() {}


Vector3d Spherical::ray_direction(const Vector2d& pp, const int hres, const int vres, const float s) const {

  // compute the normalised device coordinates
  Vector2d pn( 2.0 / (s * hres) * pp(0), 2.0 / (s * vres) * pp(1));

  // compute the angles lambda and phi in radians
  float lambda = pn(0) * lambda_max * PI_ON_180;
  float psi    = pn(1) * psi_max * PI_ON_180;

  // compute the regular azimuth and polar angles
  float phi         = PI - lambda;
  float theta   = 0.5 * PI - psi;

  float sin_phi   = sin(phi);
  float cos_phi   = cos(phi);
  float sin_theta = sin(theta);
  float cos_theta = cos(theta);

  // equation 11.6
  Vector3d dir  = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

  return dir;
}


void Spherical::render_scene(const World& w, const char* image_file) {
  RGBColor  L;
  ViewPlane vp(w.vp);
  Ray   ray;
  int   depth = 0;
  Vector2d sp;                  // sample point in [0, 1] X [0, 1]
  Vector2d pp;                  // sample point on the pixel
  const int n = vp.sampler_ptr->get_num_samples();

  ray.o = eye;

  png::image< png::rgb_pixel > image(vp.hres, vp.vres);

  for (int r = 0; r < vp.vres; r++) {   // up
    for (int c = 0; c < vp.hres; c++) { // across
      L = RGBColor(0.0, 0.0, 0.0);

      for (int j = 0; j < n; j++) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp(0) = vp.px_size * (c - 0.5 * vp.hres + sp(0));
        pp(1) = vp.px_size * (r - 0.5 * vp.vres + sp(1));
        ray.d = ray_direction(pp, vp.hres, vp.vres, vp.px_size);
        L += w.tracer_ptr->trace_ray(ray, depth);
      }

      L /= n;
      L *= exposure_time;
      w.display_pixel(r, c, L, image);
    }
  }

  image.write(image_file);
}
