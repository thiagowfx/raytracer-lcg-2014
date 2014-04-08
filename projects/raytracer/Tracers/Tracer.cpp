#include "Tracer.h"

Tracer::Tracer() :
  world_ptr(NULL)
{}


Tracer::Tracer(World* _worldPtr) :
  world_ptr(_worldPtr)
{}


Tracer::~Tracer() {
  if (world_ptr)
    world_ptr = NULL;
}


RGBColor Tracer::trace_ray(const Ray& ray) const {
  puts("INFO: Tracer::trace_ray(const Ray& ray)");
  return RGBColor();
}


RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
  puts("INFO: Tracer::trace_ray(const Ray& ray, const int depth)");
  return RGBColor();
}
