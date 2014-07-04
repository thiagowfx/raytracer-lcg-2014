#include "Whitted.h"

namespace Raytracer {
  Whitted::Whitted() :
    Tracer()
  {}


  Whitted::Whitted(World* w) :
    Tracer(w)
  {}


  Whitted::~Whitted() {}


  const char *Whitted::to_string() {
    return "Whitted";
  }


  RGBColor Whitted::trace_ray(const Ray ray, const int depth) const {
    if (depth > world_ptr->vp.max_depth)
      return black;
    else {
      ShadeRec sr(world_ptr->hit_objects(ray));
      if (sr.hit_an_object) {
        sr.depth = depth;
        sr.ray = ray;
        return sr.material_ptr->shade(sr);
      }
      else {
        return world_ptr->background_color;
      }
    }
  }
}
