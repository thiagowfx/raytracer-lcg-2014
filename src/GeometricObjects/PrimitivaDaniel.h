#ifndef __PRIMITIVADANIEL__
#define __PRIMITIVADANIEL__

// FIXME :: includes aqui
#include "GeometricObject.h"

class PrimitivaDaniel: public GeometricObject {

 public:
  PrimitivaDaniel();
  PrimitivaDaniel(const PrimitivaDaniel& pd);
  PrimitivaDaniel& operator= (const PrimitivaDaniel& pd);
  virtual ~PrimitivaDaniel();
  virtual PrimitivaDaniel* clone() const;

  virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;

 private:

};


#endif
