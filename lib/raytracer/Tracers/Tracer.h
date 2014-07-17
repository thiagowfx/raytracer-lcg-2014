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
   * @brief A tracer is responsible about which shading technique
   * should be used to render a scene.
   */
  class Tracer {
  public:
    /** Tracer classes should not be copied because of the world pointer. */
    Tracer(World*);
    virtual ~Tracer();
    /** Return the class name. */
    virtual const char* to_string() = 0;
    virtual RGBColor trace_ray(const Ray, const int depth) const = 0;
  protected:
    /** Reference to the world where the shading process will take place. */
    World* world_ptr = NULL;
  };
}

#endif // _TRACER_MINE_
