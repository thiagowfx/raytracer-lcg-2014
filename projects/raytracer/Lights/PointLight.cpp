#include "PointLight.h"

PointLight::PointLight () :
  Light(),
  ls(1.0),
  color(RGBColor(1.0, 1.0, 1.0)),
  location(Vector3d::Zero())
{}


PointLight::PointLight (const PointLight& a) :
  Light(a),
  ls(a.ls),
  color(a.color),
  location(a.location)
{}


Light* PointLight::clone() const {
  return new PointLight(*this);
}


PointLight& PointLight::operator= (const PointLight& rhs) {
  if (this != &rhs) {
    Light::operator= (rhs);
    ls        = rhs.ls;
    color     = rhs.color;
    location = rhs.location;
  }

  return *this;
}


PointLight::~PointLight () {}


Vector3d PointLight::get_direction(ShadeRec& sr) {
  return (location - sr.hit_point).normalized();
}


RGBColor PointLight::L(ShadeRec& sr) {
  return ls * color;
}


// bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
//   float t;
//   int num_objects = sr.w.objects.size();
//   float d = location.distance(ray.o);

//   for(int j = 0; j < num_objects; j++)
//     if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
//       return true;

//   return false;
// }


float PointLight::G(const ShadeRec& sr) const{
  return 5.5;
}


float PointLight::pdf(const ShadeRec& sr) const{
  return 5.5;
}
