#ifndef __PRIMITIVA_DANIEL__
#define __PRIMITIVA_DANIEL__

/* RAYTRACER */
#include <vector>
#include "GeometricObject.h"

/* PCS_DETECTION */
#include <GL/glew.h>
#include <GL/glut.h>
#include "pc-shape-detection.h"
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
  static vector<PrimitivaDaniel*> dummy(const char* path_to_shape);

 private:
  Primitive* primitive;
};


#endif
