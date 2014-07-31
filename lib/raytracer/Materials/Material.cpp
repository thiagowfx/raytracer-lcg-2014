#include "Material.h"

namespace Raytracer {
  Material::Material() {}


  Material::~Material() {}

  
  Material::Material(const Material& m) {}


  RGBColor Material::path_shade(ShadeRec &sr) {
    return black;
  }


  RGBColor Material::get_Le(ShadeRec &sr) const {
    return black;
  }
}
