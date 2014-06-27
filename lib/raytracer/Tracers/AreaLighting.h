#ifndef __AREA_LIGHTING__
#define __AREA_LIGHTING__

#include "Tracer.h"
#include "World.h"

class AreaLighting: public Tracer {

 public:
  AreaLighting();
  AreaLighting(World*);
  virtual ~AreaLighting();
  virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};

#endif
