#include "Emissive.h"

namespace Raytracer {
  Emissive::Emissive(const RGBColor& color, double radiance) :
    Material(){
    set_ce(color);
    set_radiance(radiance);
  }


  Emissive::Emissive(const Emissive& m) :
    Material(m),
    ce(m.ce),
    ls(m.ls)
  {}


  Emissive::Emissive() {}


  bool Emissive::operator==(const Emissive& o) const {
    return
      Material::operator==(o) &&
      ls == o.ls &&
      ce == o.ce;
  }


  Material* Emissive::clone() const {
    return new Emissive(*this);
  }


  Emissive::~Emissive() {}


  RGBColor Emissive::shade(ShadeRec& sr) {
    if (-sr.normal.dot(sr.ray.direction) > 0.0) {
      return ls * ce;
    }
    else {
      return black;
    }
  }


  RGBColor Emissive::area_light_shade(ShadeRec& sr) {
    if (-sr.normal.dot(sr.ray.direction) > 0.0) {
      return ls * ce;
    }
    else {
      return black;
    }
  }

  RGBColor Emissive::get_color() const {
    return ls * ce;
  }

  RGBColor Emissive::get_Le(ShadeRec& sr) const {
    return ls * ce;
  }
}
