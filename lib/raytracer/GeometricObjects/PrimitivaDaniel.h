#ifndef _PRIMITIVA_DANIEL_MINE_
#define _PRIMITIVA_DANIEL_MINE_

#include "GeometricObject.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "pc-shape-detection.h"

namespace Raytracer {
  class PrimitivaDaniel: public GeometricObject {

  public:
    PrimitivaDaniel(Primitive*);
    PrimitivaDaniel(const PrimitivaDaniel&);
    ~PrimitivaDaniel();
    virtual PrimitivaDaniel* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
    static vector<PrimitivaDaniel*> generic(const char* path_to_shape);

  private:
    Primitive* primitive;
  };
}

#endif // _PRIMITIVA_DANIEL_MINE_
