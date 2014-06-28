#ifndef __RAYTRACER_SPHERE__
#define __RAYTRACER_SPHERE__

#include "GeometricObject.h"

class RaytracerSphere: public GeometricObject {

 public:
  RaytracerSphere(Vector3d center, double r);
  RaytracerSphere(const RaytracerSphere& sphere);
  ~RaytracerSphere();
  virtual RaytracerSphere* clone() const;
  RaytracerSphere& operator= (const RaytracerSphere& sphere);
  virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

 private:
  Vector3d center;
  double radius;
};

#endif
