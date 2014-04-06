#ifndef __RAYTRACER_SPHERE__
#define __RAYTRACER_SPHERE__

#include "GeometricObject.h"

class RaytracerSphere: public GeometricObject {	
								  	
 public:
  RaytracerSphere();
  RaytracerSphere(Vector3d center, double r);
  RaytracerSphere(const RaytracerSphere& sphere);
  virtual ~RaytracerSphere();
  RaytracerSphere& operator= (const RaytracerSphere& sphere);				
  void set_center(const Vector3d& c);
  void set_radius(const double r);
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;	
		
 private:
  Vector3d center;              // center coordinates as a point  
  double radius;                // the radius 
  
};


inline void RaytracerSphere::set_center(const Vector3d& center) {
  this->center = center;
}


inline void RaytracerSphere::set_radius(const double radius) {
  this->radius = radius;
}

#endif
