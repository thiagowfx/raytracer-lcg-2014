#include "Plane.h"

Plane::Plane(void)	
  : 	GeometricObject(),
	a(Vector3d::Zero()),
	n(0, 1, 0)						
{}


Plane::Plane(const Vector3d& point, const Vector3d& normal)
  :	GeometricObject(),
	a(point),
	n(normal)
{
  n.normalize();
}


Plane::Plane(const Plane& plane) 
  :	GeometricObject(plane),
	a(plane.a),
	n(plane.n) 				
{}


Plane* Plane::clone(void) const {
  return (new Plane(*this));
}


Plane& Plane::operator= (const Plane& rhs) {
  if (this != &rhs) {
    GeometricObject::operator= (rhs);
    a = rhs.a;
    n = rhs.n;
  }

  return (*this);
}


Plane::~Plane(void) {}


bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
  float t = (a - ray.o).dot(n) / ray.d.dot(n); 
  
  if (t > kEpsilon) {
    tmin = t;
    sr.normal = n;
    sr.local_hit_point = ray.o + t * ray.d;
    
    return true;
  }
  
  return false;
}
