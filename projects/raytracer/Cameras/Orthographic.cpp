#include "Orthographic.h"

Orthographic::Orthographic() :
  Camera(),
  zw(100.0)
{}


Orthographic::Orthographic(const Orthographic& orto) :
  Camera(orto),
  zw(orto.zw)
{}


Orthographic& Orthographic::operator= (const Orthographic& rhs) {
  if (this != &rhs) {
    Camera::operator= (rhs);
    zw = rhs.zw;
  }

  return *this;
}


Orthographic::~Orthographic() {}


Orthographic* Orthographic::clone() const {
  return new Orthographic(*this);
}


void Orthographic::render_scene(const World* w, const char* image_file) {
  RGBColor L;
  ViewPlane vp(w->vp);
  Ray      ray;
  int depth = 0;
  Vector2d sp;                  // sample point in [0,1] x [0,1]
  Vector2d pp;
  const int n = vp.sampler_ptr->get_num_samples();
  
  ray.d = Vector3d(0.0, 0.0, -1.0);

  png::image< png::rgb_pixel > image(vp.hres, vp.vres);

  for (int r = 0; r < vp.vres; r++) {   // up
    for (int c = 0; c < vp.hres; c++) { // across
      L = RGBColor(0.0, 0.0, 0.0);

      for (int j = 0; j < n; ++j) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp(0) = vp.px_size * (c - 0.5 * vp.hres + sp(0));
        pp(1) = vp.px_size * (r - 0.5 * vp.vres + sp(1));
        ray.o = Vector3d(pp(0), pp(1), zw);
        // L += w->tracer_ptr->trace_ray(ray, depth);
        L += w->tracer_ptr->trace_ray(ray);
      }

      L /= n;                   // average the colors
      L *= exposure_time;
      w->display_pixel(r, c, L, image);
    }
  }

  image.write(image_file);
}
