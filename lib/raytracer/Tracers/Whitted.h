#ifndef _WHITTED_MINE_
#define _WHITTED_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief Tracer which uses the Phong Model to render scenes.
   *
   * ambient + diffuse + reflective radiance, plus (optionally)
   * reflected rays. To get a RayCasting tracer, just set 0 to the
   * maximum depth in the ViewPlane.
   */
  class Whitted: public Tracer {
  public:
    Whitted(World*);
    virtual ~Whitted();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray, const int depth) const;
  };
}

#endif // _WHITTED_MINE_
