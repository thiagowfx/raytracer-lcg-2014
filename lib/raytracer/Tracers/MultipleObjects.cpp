#include "MultipleObjects.h"

namespace Raytracer {
  MultipleObjects::MultipleObjects(World* w) :
    Tracer(w)
  {}


  MultipleObjects::~MultipleObjects() {}


  const char* MultipleObjects::to_string() {
    return "MultipleObjects";
  }


  inline RGBColor MultipleObjects::trace_ray(const Ray ray, const int depth) const {
    ShadeRec sr(world_ptr->hit_objects(ray)); // copy constructed
    if (sr.hit_an_object) {
      return sr.material_ptr->get_color();
    }
    else {
      return world_ptr->background_color;
    }
  }
}
