#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"
#include "World.h"

class MultipleObjects: public Tracer {
  
 public:		
  MultipleObjects();
  MultipleObjects(World*); 
  virtual ~MultipleObjects();
  virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};


#endif
