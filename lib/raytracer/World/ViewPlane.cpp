#include "ViewPlane.h"

namespace Raytracer {
  ViewPlane::ViewPlane() {}


  ViewPlane::ViewPlane(const ViewPlane& vp) :
    hres(vp.hres),
    vres(vp.vres),
    pixel_size(vp.pixel_size),
    inv_gamma(vp.inv_gamma),
    out_of_gamut(vp.out_of_gamut),
    max_depth(vp.max_depth) {}


  ostream& operator<<(ostream& os, const ViewPlane& vp) {
    os << vp.hres;
    os << " ";
    os << vp.vres;
    os << " ";
    os << vp.pixel_size;
    os << " ";
    os << vp.inv_gamma;
    os << " ";
    os << vp.out_of_gamut;
    os << " ";
    os << vp.max_depth;
    os << " ";
    return os;
  }


  bool ViewPlane::operator==(const ViewPlane& o) const {
    return
      hres == o.hres &&
      vres == o.vres &&
      pixel_size == o.pixel_size &&
      inv_gamma == o.inv_gamma &&
      out_of_gamut == o.out_of_gamut &&
      max_depth == o.max_depth;
  }


  ViewPlane::~ViewPlane() {}
}
