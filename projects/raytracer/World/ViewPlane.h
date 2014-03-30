#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include "MultiJittered.h"
#include "Regular.h"

class ViewPlane {
  
 public:
  int    hres;       // horizontal image resolution 
  int    vres;       // vertical image resolution
  double px_size;    // pixel size --> decrease to zoom into the image
  double gamma;      // gamma correction factor
  bool   show_out_of_gamut;	// display red if RGBColor out of gamut
  Sampler* sampler_ptr;
									
  ViewPlane(); 
  ~ViewPlane(); 
  ViewPlane(const ViewPlane& vp);
  ViewPlane& operator= (const ViewPlane& rhs);
						
  void set_hres(const int h_res);		
  void set_vres(const int v_res);				
  void set_pixel_size(const float size);		
  void set_gamma(const float g);		
  void set_show_of_gamut(const bool show);
  void set_sampler(Sampler* sp);
  void set_samples(const int n);
};


inline void ViewPlane::set_hres(const int h_res) {
  hres = h_res;
}


inline void ViewPlane::set_vres(const int v_res) {
  vres = v_res;
}


inline void ViewPlane::set_pixel_size(const float size) {
  px_size = size;
}


inline void ViewPlane::set_gamma(const float g) {
  gamma = g;
}


inline void ViewPlane::set_show_of_gamut(const bool show) {
  show_out_of_gamut = show;
}


inline void ViewPlane::set_sampler(Sampler* sp) {
  if (this->sampler_ptr) {
    delete this->sampler_ptr;
    this->sampler_ptr = NULL;
  }

  this->sampler_ptr = sp;
}

inline void ViewPlane::set_samples(const int n) {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }

  if (n > 1)
    sampler_ptr = new MultiJittered(n);
  else
    sampler_ptr = new Regular(1);
}


#endif
