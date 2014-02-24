#include "Light.h"

Light::Light() {}


Light::Light(const Light& ls) {}


Light& Light::operator= (const Light& rhs) {
  return *this;
}


Light::~Light() {} 


RGBColor Light::L(ShadeRec& s) {
  return black;
}


