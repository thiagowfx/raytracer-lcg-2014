#include "RaytracerPlane.h"

RaytracerPlane::RaytracerPlane() :
  GeometricObject(),
  point(Vector3d::Zero()),
  normal(0.0, 1.0, 0.0)						
{}


RaytracerPlane::RaytracerPlane(const Vector3d& _point, const Vector3d& _normal) :
  GeometricObject(),
  point(_point),
  normal(_normal)
{
  normal.normalize();
}


RaytracerPlane::RaytracerPlane(const RaytracerPlane& plane) :
  GeometricObject(plane),
  point(plane.point),
  normal(plane.normal) 
{}


RaytracerPlane& RaytracerPlane::operator= (const RaytracerPlane& rhs) {
  if (this != &rhs) {
    GeometricObject::operator= (rhs);
    point = rhs.point;
    normal = rhs.normal;
  }

  return *this;
}


RaytracerPlane::~RaytracerPlane() {}


bool RaytracerPlane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
  float t = (point - ray.o).dot(normal) / ray.d.dot(normal); 
  
  if (t > kEpsilon) {
    tmin = t;
    sr.normal = normal;
    sr.local_hit_point = ray.o + t * ray.d;
    
    return true;
  }
  
  return false;
}