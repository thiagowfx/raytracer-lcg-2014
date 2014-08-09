#include "Material.h"

namespace Raytracer {
  Material::Material() {}


  Material::~Material() {}

  
  Material::Material(const Material& m) {}


  bool Material::operator==(const Material&) const {
    return true;
  }


  RGBColor Material::get_Le(ShadeRec &sr) const {
    return black;
  }
}
