#ifndef __SPHERE__
#define __SPHERE__

#include "Constants.h"
#include "GeometricObject.h"
#include "math.h"

class Sphere: public GeometricObject {	
								  	
 public:
  Sphere(void);
  Sphere(Vector3d center, double r);
  Sphere(const Sphere& sphere);
  virtual Sphere* clone(void) const;
  virtual ~Sphere(void);
  Sphere& operator= (const Sphere& sphere);				
  void set_center(const Vector3d& c);
  void set_center(const double x, const double y, const double z);
  void set_radius(const double r);
  virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;	
		
 private:
  Vector3d center;              // center coordinates as a point  
  double radius;                // the radius 
  
};


inline void Sphere::set_center(const Vector3d& c) {
  center = c;
}


inline void Sphere::set_center(const double x, const double y, const double z) {
  center(0) = x;
  center(1) = y;
  center(2) = z;
}
		
inline void Sphere::set_radius(const double r) {
  radius = r;
}

#endif
