#include "RayCast.h"

RayCast::RayCast() :
  Tracer()
{}


RayCast::RayCast(World* _worldPtr) :
  Tracer(_worldPtr)
{}


RayCast::~RayCast() {}


RGBColor RayCast::trace_ray(const Ray ray, const int depth) const {
  ShadeRec sr(world_ptr->hit_objects(ray));

  if (sr.hit_an_object) {
    sr.ray = ray;               // used for specular shading
    return sr.material_ptr->shade(sr);
  }
  else
    return world_ptr->background_color;
}
