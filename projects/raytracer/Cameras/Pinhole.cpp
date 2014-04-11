#include "Pinhole.h"

Pinhole::Pinhole() :
  Camera(),
  d(500),
  zoom(1.0)
{}


Pinhole::Pinhole(const Pinhole& c) :
  Camera(c),
  d(c.d),
  zoom(c.zoom)
{}


Pinhole& Pinhole::operator= (const Pinhole& rhs) {
  if (this != &rhs) {
    Camera::operator= (rhs);
    d    = rhs.d;
    zoom = rhs.zoom;
  }

  return *this;
}


Pinhole::~Pinhole() {}


Vector3d Pinhole::get_direction(const Vector2d& p) const {
  Vector3d dir = (p(0) * u) + (p(1) * v) - (d * w);
  dir.normalize();
	
  return dir;
}


Pinhole* Pinhole::clone() const {
  return new Pinhole(*this);
}


void Pinhole::render_scene(const World& w, const char* image_file) {
  RGBColor  L;
  ViewPlane vp(w.vp);
  Ray	    ray;
  int 	    depth = 0;
  Vector2d  sp;                 // sample point in [0,1] x [0,1]
  Vector2d  pp;                 // sample point on a pixel
  const int n = vp.sampler_ptr->get_num_samples();
		
  vp.px_size /= zoom;
  ray.o = eye;

  png::image< png::rgb_pixel > image(vp.hres, vp.vres);
		
  for (int r = 0; r < vp.vres; r++) { // up
    for (int c = 0; c < vp.hres; c++) { // across 					
      L = RGBColor(0.0, 0.0, 0.0);

      for (int j = 0; j < n; ++j) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp(0) = vp.px_size * (c - 0.5 * vp.hres + sp(0));
        pp(1) = vp.px_size * (r - 0.5 * vp.vres + sp(1));
        ray.d = get_direction(pp);
        L += w.tracer_ptr->trace_ray(ray, depth);
      }
			
      L /= n;
      L *= exposure_time;
      w.display_pixel(r, c, L, image);
    }
  }

  image.write(image_file);
}