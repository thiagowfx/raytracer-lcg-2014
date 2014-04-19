#include "Ambient.h"

Ambient::Ambient () :
  Light(),
  radiance(1.0),
  color(1.0, 1.0, 1.0)
{}


Ambient::Ambient (const Ambient& a) :
  Light(a),
  radiance(a.radiance),
  color(a.color) 		
{}


Light* Ambient::clone() const {
  return new Ambient(*this);
}	


Ambient& Ambient::operator= (const Ambient& rhs) {
  if (this != &rhs) {
    Light::operator= (rhs);    
    radiance 	  = rhs.radiance;
    color = rhs.color;
  }
	
  return *this;
}


Ambient::~Ambient () {}


Vector3d Ambient::get_direction(ShadeRec& s) {
  return Vector3d(Vector3d::Zero());
}


RGBColor Ambient::L(ShadeRec& sr) {	
  return radiance * color;
}


bool Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const {
  return false;
}
