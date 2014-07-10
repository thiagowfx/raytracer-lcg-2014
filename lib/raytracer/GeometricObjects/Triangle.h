#ifndef _TRIANGLE_MINE_
#define _TRIANGLE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Triangle: public GeometricObject {

  public:
    /** Construct a triangle with the given vertexes. Normal is defined by counter-clockwise vertexes. */
    Triangle(const Vector3d&, const Vector3d&, const Vector3d&);
    Triangle(const Triangle&);
    ~Triangle();
    virtual Triangle* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    void compute_normal();
    
    /* Vertexes of triangle. */
    Vector3d v0, v1, v2;

    /* Normal. */
    Vector3d normal;
  };
}

#endif // _TRIANGLE_MINE_
