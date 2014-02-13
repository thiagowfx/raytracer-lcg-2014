#include "Ray.h"

Ray::Ray (void)
  : 	o(Vector3d::Zero()),
	d(0.0, 0.0, 1.0) 
{}

Ray::Ray (const Vector3d& origin, const Vector3d& dir)
  : 	o(origin), 
	d(dir) 
{}

Ray::Ray (const Ray& ray)
  : 	o(ray.o), 
	d(ray.d) 
{}

Ray& Ray::operator= (const Ray& rhs) {
	
  if (this != &rhs) {
    o = rhs.o; 
    d = rhs.d;
  }

  return (*this);	
}

Ray::~Ray (void) {}
