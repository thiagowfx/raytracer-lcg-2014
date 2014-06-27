#ifndef __RAYTRACER_PLANE__
#define __RAYTRACER_PLANE__

#include "GeometricObject.h"

class RaytracerPlane : public GeometricObject {
	
 public:
  RaytracerPlane();
  virtual ~RaytracerPlane();
  virtual RaytracerPlane* clone() const;
  RaytracerPlane(const Vector3d& point, const Vector3d& normal);
  RaytracerPlane(const RaytracerPlane& plane);
  RaytracerPlane& operator= (const RaytracerPlane& rhs);	
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
  virtual bool shadow_hit(const Ray& ray, double& tmin) const;
		
 private:
  Vector3d point;   		// point through which plane passes 
  Vector3d normal;
};

#endif
