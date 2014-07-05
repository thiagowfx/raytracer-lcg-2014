#include "ShadeRec.h"

namespace Raytracer {
  ShadeRec::ShadeRec(World& wr) :
    w(wr)
  {}

  
  ShadeRec::~ShadeRec() {}

  
  ShadeRec::ShadeRec(const ShadeRec& sr) :
    hit_an_object(sr.hit_an_object),
    material_ptr(sr.material_ptr),
    hit_point(sr.hit_point),
    local_hit_point(sr.local_hit_point),
    normal(sr.normal),
    ray(sr.ray),
    depth(sr.depth),
    t(sr.t),
    w(sr.w)
  {}
}
