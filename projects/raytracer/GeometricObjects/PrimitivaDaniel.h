#ifndef __PRIMITIVA_DANIEL__
#define __PRIMITIVA_DANIEL__

/* RAYTRACER */
#include "GeometricObject.h"

/* PCS_DETECTION */
#include "primitive.h"

class PrimitivaDaniel: public GeometricObject {

 public:
  PrimitivaDaniel();
  PrimitivaDaniel(Primitive*);
  ~PrimitivaDaniel();
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

 private:
  Primitive* primitive;
};


#endif
