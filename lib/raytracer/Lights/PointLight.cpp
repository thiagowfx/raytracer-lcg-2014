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
      ls = rhs.ls;
      color = rhs.color;
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


/** Chapter 16 */
bool PointLight::in_shadow(const Ray& ray, ShadeRec& sr) const {
  double t = 0;
  const int num_objects = sr.w.objects.size();
  const double distance = (location - ray.o).norm();

  for (int j = 0; j < num_objects; j++)
    /** t < d means: an object only blocks a point light if it is before the light */
    if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr) && t < distance)
      return true;

  return false;
}
