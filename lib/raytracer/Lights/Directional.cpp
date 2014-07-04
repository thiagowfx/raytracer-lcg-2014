#include "Directional.h"

namespace Raytracer {
  Directional::Directional() :
    Light()
  {}


  Directional::Directional(const Directional& dl) :
    Light(dl),
    ls(dl.ls),
    color(dl.color),
    direction(dl.direction)
  {}


  Light* Directional::clone() const {
    return new Directional(*this);
  }


  Directional& Directional::operator= (const Directional& rhs) {
    if (this != &rhs) {
      Light::operator= (rhs);
      ls          = rhs.ls;
      color = rhs.color;
      direction   = rhs.direction;
    }
    return *this;
  }


  Directional::~Directional() {}


  /* as this function is virtual, it shouldn't be inlined */
  Vector3d Directional::get_direction(ShadeRec& sr) {
    return direction;
  }


  RGBColor Directional::L(ShadeRec& s) {
    return ls * color;
  }


  bool Directional::in_shadow(const Ray& ray, ShadeRec& sr) const {
    double t;
    const int num_objects = sr.w.objects.size();

    for (int j = 0; j < num_objects; j++)
      if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr))
        return true;

    return false;
  }
}
