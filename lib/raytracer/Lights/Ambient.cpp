#include "Ambient.h"

namespace Raytracer {
  Ambient::Ambient () :
    Light()
  {}


  Ambient::Ambient(const Ambient& a) :
    Light(a),
    ls(a.ls),
    color(a.color)
  {}


  Light* Ambient::clone() const {
    return new Ambient(*this);
  }


  Ambient::~Ambient () {}


  Vector3d Ambient::get_direction(ShadeRec& s) {
    return Vector3d(Vector3d::Zero());
  }


  RGBColor Ambient::L(ShadeRec& sr) {
    return ls * color;
  }


  const char* Ambient::to_string() const {
    return "Ambient";
  }

  
  bool Ambient::in_shadow(const Ray& ray, ShadeRec& sr) const {
    return false;
  }
}
