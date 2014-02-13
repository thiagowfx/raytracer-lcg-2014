#ifndef __PLANE__
#define __PLANE__

#include "Constants.h"
#include "GeometricObject.h"

class Plane : public GeometricObject {
	
 public:
  Plane(void);
  Plane(const Vector3d& point, const Vector3d& normal);
  Plane(const Plane& plane);
  virtual Plane* clone(void) const;
  Plane& operator= (const Plane& rhs);	
  virtual ~Plane(void);
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
 private:
  Vector3d a;   		// point through which plane passes 
  Vector3d n;                   // normal to the plane
  
};

#endif
