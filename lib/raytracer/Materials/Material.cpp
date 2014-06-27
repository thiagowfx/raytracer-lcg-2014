#include "Material.h"

Material::Material() {}

Material::Material(const Material& m) {}

RGBColor Material::area_light_shade(ShadeRec &sr) {
  return black;
}

RGBColor Material::path_shade(ShadeRec &sr) {
  return black;
}

RGBColor Material::get_Le(ShadeRec &sr) const {
  return black;
}

Material& Material::operator= (const Material& rhs) {
  return *this;
}

Material::~Material() {}
