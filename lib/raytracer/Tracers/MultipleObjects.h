#ifndef _MULTIPLE_OBJECTS_MINE_
#define _MULTIPLE_OBJECTS_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief Simplest tracer, only shades color of objects, using no lighting information at all.
   */
  class MultipleObjects: public Tracer {
  public:
    MultipleObjects(World*);
    virtual ~MultipleObjects();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray, const int depth) const;
  };
}

#endif // _MULTIPLE_OBJECTS_MINE_
