#ifndef _SPHERE_MINE_
#define _SPHERE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Sphere: public GeometricObject {

  public:
    Sphere(Vector3d center, double r);
    Sphere(const Sphere& sphere);
    ~Sphere();
    virtual Sphere* clone() const;
    Sphere& operator= (const Sphere& sphere);
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

  private:
    Vector3d center;
    double radius;
  };
}

#endif // _SPHERE_MINE_