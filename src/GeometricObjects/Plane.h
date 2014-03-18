#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.h"

class Plane : public GeometricObject {
	
 public:
  Plane();
  virtual ~Plane();
  Plane(const Vector3d& point, const Vector3d& normal);
  Plane(const Plane& plane);
  virtual Plane* clone() const;
  Plane& operator= (const Plane& rhs);	
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
 private:
  Vector3d point;   		// point through which plane passes 
  Vector3d normal;
  
};

#endif
