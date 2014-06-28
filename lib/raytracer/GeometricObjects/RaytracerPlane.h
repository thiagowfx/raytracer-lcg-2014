#ifndef __RAYTRACER_PLANE__
#define __RAYTRACER_PLANE__

#include "GeometricObject.h"

class RaytracerPlane : public GeometricObject {

 public:
  ~RaytracerPlane();
  virtual RaytracerPlane* clone() const;
  RaytracerPlane(const Vector3d& point, Vector3d normal);
  RaytracerPlane(const RaytracerPlane& plane);
  RaytracerPlane& operator= (const RaytracerPlane& rhs);
  virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

 private:
  Vector3d point;
  Vector3d normal;
};

#endif
