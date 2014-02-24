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
  Vector3d dir = p(0) * u + p(1) * v - d * w;
  dir.normalize();
	
  return dir;
}


void Pinhole::render_scene(const World& w, FILE *fp) {
  RGBColor  L;
  ViewPlane vp(w.vp);
  Ray	    ray;
  int 	    depth = 0;  
  Vector2d  pp;                 // sample point on a pixel
  int       n     = (int)sqrt((float)vp.num_samples);
		
  vp.s /= zoom;
  ray.o = eye;

  fprintf(fp, "%d %d\n", vp.hres, vp.vres);
		
  for (int r = 0; r < vp.vres; r++) // up
    for (int c = 0; c < vp.hres; c++) { // across 					
      L = black; 
			
      for (int p = 0; p < n; p++)     // up pixel
        for (int q = 0; q < n; q++) { // across pixel
          pp(0) = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n); 
          pp(1) = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
          ray.d = get_direction(pp);
          L += w.tracer_ptr->trace_ray(ray, depth);
        }	
											
      L /= vp.num_samples;
      L *= exposure_time;
      w.display_pixel(r, c, L, fp);
    } 
}
