#ifndef _TRIANGLE_MINE_
#define _TRIANGLE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Triangle: public GeometricObject {

  public:
    Triangle(const Vector3d& a, const Vector3d& b, const Vector3d& c);
    virtual Triangle* clone() const;
    Triangle(const Triangle& triangle);
    ~Triangle();
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

  private:
    Vector3d v0, v1, v2;
    Vector3d normal;
    void compute_normal();
  };
}

#endif // _TRIANGLE_MINE_
