#include "PointLight.h"

PointLight::PointLight () :
  Light(),
  radiance(1.0),
  color(RGBColor(1.0, 1.0, 1.0)),
  location(Vector3d::Zero())
{}


PointLight::PointLight (const PointLight& a) :
  Light(a),
  radiance(a.radiance),
  color(a.color),
  location(a.location)
{}


Light* PointLight::clone() const {
  return new PointLight(*this);
}


PointLight& PointLight::operator= (const PointLight& rhs) {
  if (this != &rhs) {
      Light::operator= (rhs);
      radiance = rhs.radiance;
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
  return radiance * color;
}


bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
  double t = 0;
  const int num_objects = sr.w.objects.size();
  double d = (location - ray.o).norm();

  for (int j = 0; j < num_objects; j++)
    if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
      return true;

  return false;
}
