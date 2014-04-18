/* The tracer classes have no copy constructor, assignment operator. or clone function because 
   of the world pointer, which should not be assigned or copy constructed
   See comments in the World.h file. */

#ifndef __TRACER__
#define __TRACER__

#include "Constants.h"
#include "Material.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"

class World;

class Tracer {
  
 public:
  Tracer();
  Tracer(World*);
  virtual ~Tracer(); 
  virtual RGBColor trace_ray(const Ray ray, const int depth) const = 0;
				
 protected:
  World* world_ptr;
};


#endif
