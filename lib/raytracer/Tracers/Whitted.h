#ifndef _WHITTED_MINE_
#define _WHITTED_MINE_

#include "Tracer.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief Tracer which uses the Phong Model.
   *
   * Tracer which uses the Phong Model: ambient + diffuse + reflective radiance,
   * plus (optionally) reflected rays. To get a RayCast tracer, just set the
   * maximum depth in the ViewPlane to 0.
   */
  class Whitted: public Tracer {
  public:
    Whitted(World*);
    virtual ~Whitted();
    virtual const char* to_string();
    virtual RGBColor trace_ray(const Ray ray, const int depth) const;
  };
}

#endif // _WHITTED_MINE_
