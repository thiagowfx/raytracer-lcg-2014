#include "ViewPlane.h"

namespace Raytracer {
  ViewPlane::ViewPlane() {}


  ViewPlane::ViewPlane(const ViewPlane& vp) :
    hres(vp.hres),
    vres(vp.vres),
    pixel_size(vp.pixel_size),
    gamma(vp.gamma),
    out_of_gamut(vp.out_of_gamut),
    max_depth(vp.max_depth) {
    if (vp.sampler_ptr)
      sampler_ptr = vp.sampler_ptr->clone();
  }


  ViewPlane::~ViewPlane() {
    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }
  }
}
