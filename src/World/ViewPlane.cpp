#include "ViewPlane.h"
	
ViewPlane::ViewPlane() :
  hres(400), 
  vres(400),
  px_size(1.0),
  gamma(1.0),
  show_out_of_gamut(false),
  sampler_ptr(NULL)
{
  set_samples(1);
}


ViewPlane::ViewPlane(const ViewPlane& vp) :
  hres(vp.hres),  
  vres(vp.vres), 
  px_size(vp.px_size),
  gamma(vp.gamma),
  show_out_of_gamut(vp.show_out_of_gamut)
{
  if (vp.sampler_ptr)
    sampler_ptr = vp.sampler_ptr->clone();
  else
    sampler_ptr = NULL;
}


ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
  if (this != &rhs) {		
    hres 	      = rhs.hres;
    vres 	      = rhs.vres;
    px_size       = rhs.px_size;
    gamma	      = rhs.gamma;
    show_out_of_gamut = rhs.show_out_of_gamut;

    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }

    if (rhs.sampler_ptr)
      sampler_ptr = rhs.sampler_ptr->clone();
  }
	
  return *this;
}

ViewPlane::~ViewPlane() {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
}
