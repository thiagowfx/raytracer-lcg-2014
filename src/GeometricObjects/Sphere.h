#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.h"

class Sphere: public GeometricObject {	
								  	
 public:
  Sphere();
  Sphere(Vector3d center, double r);
  Sphere(const Sphere& sphere);
  virtual ~Sphere();
  virtual Sphere* clone() const;
  Sphere& operator= (const Sphere& sphere);				
  void set_center(const Vector3d& c);
  void set_radius(const double r);
  virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;	
		
 private:
  Vector3d center;              // center coordinates as a point  
  double radius;                // the radius 
  
};


inline void Sphere::set_center(const Vector3d& center) {
  this->center = center;
}


inline void Sphere::set_radius(const double radius) {
  this->radius = radius;
}

#endif
