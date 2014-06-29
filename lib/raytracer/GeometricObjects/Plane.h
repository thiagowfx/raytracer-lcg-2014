#ifndef __RAYTRACER_PLANE__
#define __RAYTRACER_PLANE__

#include "GeometricObject.h"

namespace Raytracer {
  class Plane : public GeometricObject {

  public:
    ~Plane();
    virtual Plane* clone() const;
    Plane(const Vector3d& point, Vector3d normal);
    Plane(const Plane& plane);
    Plane& operator= (const Plane& rhs);
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

  private:
    Vector3d point;
    Vector3d normal;
  };
}

#endif
