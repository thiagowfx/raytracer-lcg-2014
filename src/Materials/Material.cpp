#include "Material.h"

Material::Material() {}


Material::Material(const Material& m) {}


Material& Material::operator= (const Material& rhs) {
  return *this;
}


Material::~Material() {}


RGBColor Material::shade(ShadeRec& sr) {
  return black;
}



