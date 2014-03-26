#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

class MultipleObjects: public Tracer {
  
 public:		
  MultipleObjects();
  MultipleObjects(World* _world_ptr);				
  virtual ~MultipleObjects();
  virtual RGBColor trace_ray(const Ray& ray) const;
  /* This is not used for now. Included only for compatibility purposes. */
  virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};


#endif
