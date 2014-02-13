#include "ViewPlane.h"
	
ViewPlane::ViewPlane(void)							
  : 	hres(400), 
	vres(400),
	s(1.0),
	gamma(1.0),
	inv_gamma(1.0),
	show_out_of_gamut(false),
	num_samples(1)
{}


ViewPlane::ViewPlane(const ViewPlane& vp)   
  :  	hres(vp.hres),  
	vres(vp.vres), 
	s(vp.s),
	gamma(vp.gamma),
	inv_gamma(vp.inv_gamma),
	show_out_of_gamut(vp.show_out_of_gamut),
	num_samples(vp.num_samples)
{}


ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
  if (this != &rhs) {		
    hres 		    = rhs.hres;
    vres 		    = rhs.vres;
    s		    = rhs.s;
    gamma		    = rhs.gamma;
    inv_gamma	    = rhs.inv_gamma;
    show_out_of_gamut = rhs.show_out_of_gamut;
    num_samples	    = rhs.num_samples;
  }
	
  return (*this);
}


ViewPlane::~ViewPlane(void) {}
