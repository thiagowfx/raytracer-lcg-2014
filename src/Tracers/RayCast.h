#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Material.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "World.h"

class RayCast: public Tracer {
  
 public:
  RayCast();
  RayCast(World* _worldPtr);
  virtual ~RayCast();		
  virtual RGBColor trace_ray(const Ray& ray) const;
  virtual RGBColor trace_ray(const Ray ray, const int depth) const;
  
};

#endif
