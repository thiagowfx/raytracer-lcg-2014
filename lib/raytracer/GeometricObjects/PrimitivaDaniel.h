#ifndef _PRIMITIVADANIEL_MINE_
#define _PRIMITIVADANIEL_MINE_

#include <GL/glew.h>
#include <GL/glut.h>
#include "GeometricObject.h"
#include "pc-shape-detection.h"

namespace Raytracer {
  /** An abstraction to the point cloud detection library. */
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

#endif // _PRIMITIVADANIEL_MINE_
