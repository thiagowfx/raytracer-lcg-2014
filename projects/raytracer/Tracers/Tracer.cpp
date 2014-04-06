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
