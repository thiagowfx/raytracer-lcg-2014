#ifndef _TRACER_MINE_
#define _TRACER_MINE_

#include "Material.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Utilities.h"
class World;

/** @brief Tracer
 *
 * The tracer classes have no copy constructor,assignment operator or
 * clone function because of the world pointer, which should not be
 * assigned or copy constructed.
 *
 */
class Tracer {
 public:
  Tracer();
  Tracer(World*);
  virtual ~Tracer();
  virtual RGBColor trace_ray(const Ray ray, const int depth) const = 0;

 protected:
  World* world_ptr = NULL;
};

#endif // _TRACER_MINE_
