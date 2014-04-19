#ifndef __RAYTRACER_SPHERE__
#define __RAYTRACER_SPHERE__

#include "GeometricObject.h"

class RaytracerSphere: public GeometricObject {	
								  	
 public:
  RaytracerSphere();
  RaytracerSphere(Vector3d center, double r);
  RaytracerSphere(const RaytracerSphere& sphere);
  virtual ~RaytracerSphere();
  virtual RaytracerSphere* clone() const;
  RaytracerSphere& operator= (const RaytracerSphere& sphere);				
  void set_center(const Vector3d&);
  void set_center(double,double,double);
  void set_radius(double);
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;	
  bool shadow_hit(const Ray& ray, double& tmin) const;
		
 private:
  Vector3d center;
  double radius;
};


inline void RaytracerSphere::set_center(const Vector3d& center) {
  this->center = center;
}


inline void RaytracerSphere::set_center(double x, double y, double z) {
    center(0) = x;
    center(1) = y;
    center(2) = z;
}


inline void RaytracerSphere::set_radius(double radius) {
  this->radius = radius;
}

#endif
