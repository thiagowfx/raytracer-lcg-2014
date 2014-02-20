#include "Plane.h"

Plane::Plane()	
  : 	GeometricObject(),
	point(Vector3d::Zero()),
	normal(0, 1, 0)						
{}


Plane::Plane(const Vector3d& _point, const Vector3d& _normal)
  :	GeometricObject(),
	point(_point),
	normal(_normal)
{
  normal.normalize();
}


Plane::Plane(const Plane& plane) 
  :	GeometricObject(plane),
	point(plane.point),
	normal(plane.normal) 
{}


Plane* Plane::clone() const {
  return new Plane(*this);
}


Plane& Plane::operator= (const Plane& rhs) {
  if (this != &rhs) {
    GeometricObject::operator= (rhs);
    point = rhs.point;
    normal = rhs.normal;
  }

  return *this;
}


Plane::~Plane() {}


bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
  float t = (point - ray.o).dot(normal) / ray.d.dot(normal); 
  
  if (t > kEpsilon) {
    tmin = t;
    sr.normal = normal;
    sr.local_hit_point = ray.o + t * ray.d;
    
    return true;
  }
  
  return false;
}
