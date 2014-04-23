#include "Material.h"

Material::Material() {}


Material::Material(const Material& m) {}

RGBColor Material::whitted_shade(ShadeRec &src) {
  return black;
}

RGBColor Material::area_light_shade(ShadeRec &sr) {
  return black;
}

RGBColor Material::path_shade(ShadeRec &sr) {
  return black;
}


Material& Material::operator= (const Material& rhs) {
  return *this;
}


Material::~Material() {}
