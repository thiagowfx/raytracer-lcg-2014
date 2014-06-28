#include "ViewPlane.h"


ViewPlane::ViewPlane() {
  sampler_ptr = NULL;
  set_samples(1);
}


ViewPlane::ViewPlane(const ViewPlane& vp) :
  hres(vp.hres),
  vres(vp.vres),
  px_size(vp.px_size),
  gamma(vp.gamma),
  show_out_of_gamut(vp.show_out_of_gamut),
  max_depth(vp.max_depth),
  sampler_ptr(NULL)
{
  if (vp.sampler_ptr)
    sampler_ptr = vp.sampler_ptr->clone();
}


ViewPlane::~ViewPlane() {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
}
