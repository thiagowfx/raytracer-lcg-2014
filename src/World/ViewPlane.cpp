#include "ViewPlane.h"
	
ViewPlane::ViewPlane() :
  hres(400), 
  vres(400),
  px_size(1.0),
  gamma(1.0),
  show_out_of_gamut(false),
  num_samples(1)
{}


ViewPlane::ViewPlane(const ViewPlane& vp) :
  hres(vp.hres),  
  vres(vp.vres), 
  px_size(vp.px_size),
  gamma(vp.gamma),
  show_out_of_gamut(vp.show_out_of_gamut),
  num_samples(vp.num_samples)
{}


ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
  if (this != &rhs) {		
    hres 	      = rhs.hres;
    vres 	      = rhs.vres;
    px_size       = rhs.px_size;
    gamma	      = rhs.gamma;
    show_out_of_gamut = rhs.show_out_of_gamut;
    num_samples       = rhs.num_samples;
  }
	
  return *this;
}

ViewPlane::~ViewPlane() {}
