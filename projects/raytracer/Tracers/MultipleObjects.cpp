#include "MultipleObjects.h"

MultipleObjects::MultipleObjects() :
  Tracer()
{}


MultipleObjects::MultipleObjects(World* _worldPtr) :
  Tracer(_worldPtr)
{}


MultipleObjects::~MultipleObjects() {}


inline RGBColor MultipleObjects::trace_ray(const Ray ray, const int depth) const {
    ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed

    if (sr.hit_an_object) {
      return sr.color;
    }
    else
        return world_ptr->background_color;
}
