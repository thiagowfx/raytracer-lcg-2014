#ifndef _AREALIGHTING_MINE_
#define _AREALIGHTING_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief It's like the Whitted tracer, but additionally there is support for emissive objects, which create area lights.
   */
  class AreaLighting: public Tracer {
  public:
    AreaLighting(World*);
    virtual ~AreaLighting();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray, const int depth) const;
  };
}

#endif // _AREALIGHTING_MINE_
