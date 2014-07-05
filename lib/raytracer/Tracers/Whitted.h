#ifndef _WHITTED_MINE_
#define _WHITTED_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  class Whitted: public Tracer {
  public:
    Whitted(World*);
    virtual ~Whitted();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray ray, const int depth) const;
  };
}

#endif // _WHITTED_MINE_
