#include "Light.h"

Light::Light() {}


Light::Light(const Light& ls) :
    shadows(ls.casts_shadows())
{}


Light& Light::operator= (const Light& rhs) {
  return *this;
}


Light::~Light() {}


RGBColor Light::L(ShadeRec& s) {
  return black;
}


void Light::set_shadows(const bool shadow){
  shadows = shadow;
}


bool Light::casts_shadows() const {
  return shadows;
}


double Light::G(const ShadeRec& sr) const {
  return 1.0;
}


double Light::pdf(const ShadeRec& sr) const {
  return 1.0;
}
