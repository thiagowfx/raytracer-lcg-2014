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
  PrimitivaDaniel(const PrimitivaDaniel&);
  ~PrimitivaDaniel();
  virtual PrimitivaDaniel* clone() const;
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
  virtual bool shadow_hit(const Ray& ray, double& tmin) const;

 private:
  Primitive* primitive;
};


#endif
