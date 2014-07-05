#include "Emissive.h"

namespace Raytracer {
  Emissive::Emissive() :
    Material(),
    ls(1.0),
    ce(white)
  {}


  Emissive::Emissive(const Emissive& m) :
    Material(m),
    ls(m.ls),
    ce(m.ce)
  {}


  Material* Emissive::clone() const {
    return new Emissive(*this);
  }


  Emissive& Emissive::operator= (const Emissive& rhs) {
    if (this != &rhs) {
      Material::operator=(rhs);
    }
    return *this;
  }


  Emissive::~Emissive() {}


  RGBColor Emissive::shade(ShadeRec& sr) {
    if (-sr.normal.dot(sr.ray.direction) > 0.0)
      return ls * ce;
    else
      return black;
  }


  RGBColor Emissive::area_light_shade(ShadeRec& sr) {
    if (-sr.normal.dot(sr.ray.direction) > 0.0)
      return ls * ce;
    else
      return black;
  }

  RGBColor Emissive::get_color() const {
    return ls * ce;
  }

  Emissive *Emissive::dummy(RGBColor c, double radiance = 1.0) {
    Emissive* em = new Emissive();
    em->set_ce(c);
    em->scale_radiance(radiance);
    return em;
  }


  RGBColor Emissive::get_Le(ShadeRec& sr) const {
    return ls * ce;
  }
}
