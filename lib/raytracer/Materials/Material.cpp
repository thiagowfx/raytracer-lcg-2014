#include "Material.h"

namespace Raytracer {
  Material::Material() {}


  Material::~Material() {}

  
  Material::Material(const Material& m) {}


  RGBColor Material::get_Le(ShadeRec &sr) const {
    return black;
  }
}
