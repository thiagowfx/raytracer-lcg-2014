#include "Directional.h"

Directional::Directional() :
  Light(),
  radiance(1.0),
  color(1.0, 1.0, 1.0),
  dir(0.0, 1.0, 0.0)			
{}


Directional::Directional(const Directional& dl) :
  Light(dl),
  radiance(dl.radiance),
  color(dl.color),
  dir(dl.dir)  		
{}


Light* Directional::clone() const {
  return new Directional(*this);
}


Directional& Directional::operator= (const Directional& rhs) {
  if (this != &rhs) {
    Light::operator= (rhs);
    radiance	  = rhs.radiance;
    color = rhs.color;
    dir   = rhs.dir;
  }
  
  return *this;
}


Directional::~Directional() {}


/* as this function is virtual, it shouldn't be inlined */
Vector3d Directional::get_direction(ShadeRec& sr) {
  return dir;
}	


RGBColor Directional::L(ShadeRec& s) {	
  return radiance * color;
}


bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const {
  double t;
  const int num_objects = sr.w.objects.size();
  //float d = location.distance(ray.o);

  for (int j = 0; j < num_objects; j++)
    if (sr.w.objects[j]->shadow_hit(ray, t))// && t < d)
      return true;

  return false;
}
