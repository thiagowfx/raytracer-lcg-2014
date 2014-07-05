#ifndef _AREALIGHTING_MINE_
#define _AREALIGHTING_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  class AreaLighting: public Tracer {
  public:
    AreaLighting(World*);
    virtual ~AreaLighting();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray ray, const int depth) const;
  };
}

#endif // _AREALIGHTING_MINE_
