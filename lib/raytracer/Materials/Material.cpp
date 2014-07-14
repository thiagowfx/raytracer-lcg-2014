#include "Material.h"

namespace Raytracer {
  Material::Material() {}


  Material::~Material() {}

  
  Material::Material(const Material& m) {}


  RGBColor Material::area_light_shade(ShadeRec &sr) {
    return RGBColor(0.0,0.0,0.0);
  }


  RGBColor Material::path_shade(ShadeRec &sr) {
    return RGBColor(0.0,0.0,0.0);
  }


  RGBColor Material::get_Le(ShadeRec &sr) const {
    return RGBColor(0.0,0.0,0.0);
  }
}
