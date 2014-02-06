// This file contains the definition of the class sphere

#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void)	
  : 	GeometricObject(),
	center(Vector3d::Zero()),
	radius(1.0)
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Vector3d c, double r)
  : 	GeometricObject(),
	center(c),
	radius(r)
{}


// ---------------------------------------------------------------- clone

Sphere* 
Sphere::clone(void) const {
  return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere)
  : 	GeometricObject(sphere),
	center(sphere.center),
	radius(sphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
  if (this == &rhs)
    return (*this);

  GeometricObject::operator= (rhs);

  center 	= rhs.center;
  radius	= rhs.radius;

  return (*this);
}


// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  double 		t;
  Vector3d	temp 	= ray.o - center;
  double 		a 		= ray.d.dot(ray.d);
  double 		b 		= 2.0 * temp.dot(ray.d);
  double 		c 		= temp.dot(temp) - radius * radius;
  double 		disc	= b * b - 4.0 * a * c;
	
  if (disc < 0.0)
    return(false);
  else {	
    double e = sqrt(disc);
    double denom = 2.0 * a;
    t = (-b - e) / denom;    // smaller root
	
    if (t > kEpsilon) {
      tmin = t;
      sr.normal 	 = (temp + t * ray.d) / radius;
      sr.local_hit_point = ray.o + t * ray.d;
      return (true);
    } 
	
    t = (-b + e) / denom;    // larger root
	
    if (t > kEpsilon) {
      tmin = t;
      sr.normal   = (temp + t * ray.d) / radius;
      sr.local_hit_point = ray.o + t * ray.d;
      return (true);
    } 
  }
	
  return (false);
}
