#ifndef _TRACER_MINE_
#define _TRACER_MINE_

#include "Material.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Utilities.h"

namespace Raytracer {
  class World;

  /**
   * Tracer classes should not be copied, because of the world pointer.
   */
  class Tracer {
  public:
    Tracer();
    Tracer(World*);
    virtual ~Tracer();
    virtual const char* to_string() = 0;
    virtual RGBColor trace_ray(const Ray ray, const int depth) const = 0;

  protected:
    World* world_ptr = NULL;
  };
}

#endif // _TRACER_MINE_
