#include "Tracer.h"

namespace Raytracer {
  Tracer::Tracer(World* w) :
    world_ptr(w)
  {}


  Tracer::~Tracer() {
    if (world_ptr) {
      world_ptr = NULL;
    }
  }
}
