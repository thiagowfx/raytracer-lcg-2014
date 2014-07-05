#include "AreaLight.h"

namespace Raytracer {
  AreaLight::AreaLight() :
    Light()
  {}


  AreaLight::AreaLight(const AreaLight& al) :
    Light(al)
  {
    if(al.object_ptr)
      object_ptr = al.object_ptr->clone();
    else
      object_ptr = NULL;

    if(al.material_ptr)
      material_ptr = al.material_ptr->clone();
    else
      material_ptr = NULL;
  }


  Light* AreaLight::clone() const {
    return new AreaLight(*this);
  }


  AreaLight::~AreaLight() {
    if (object_ptr) {
      delete object_ptr;
      object_ptr = NULL;
    }
    if (material_ptr) {
      delete material_ptr;
      material_ptr = NULL;
    }
  }


  AreaLight& AreaLight::operator= (const AreaLight& rhs) {
    if (this != &rhs) {
      Light::operator=(rhs);
      if (object_ptr) {
        delete object_ptr;
        object_ptr = NULL;
      }
      if (rhs.object_ptr)
        object_ptr = rhs.object_ptr->clone();
      if (material_ptr) {
        delete material_ptr;
        material_ptr = NULL;
      }
      if (rhs.material_ptr)
        material_ptr = rhs.material_ptr->clone();
    }
    return *this;
  }


  Vector3d AreaLight::get_direction(ShadeRec& sr) {
    sample_point = object_ptr->sample(); // used in the G function
    light_normal = object_ptr->get_normal(sample_point);
    wi = sample_point - sr.hit_point; // used in the G function
    wi.normalize();
    return wi;
  }


  RGBColor AreaLight::L(ShadeRec& sr) {
    double ndotd = -light_normal.dot(wi);
    if (ndotd > 0.0)
      return (material_ptr->get_Le(sr));
    else
      return black;
  }


  bool AreaLight::in_shadow(const Ray& ray, ShadeRec& sr) const {
    double t;
    int num_objects = sr.w.objects.size();
    double ts = (sample_point - ray.origin).dot(ray.direction);

    for (int j = 0; j < num_objects; j++)
      if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr) && t < ts)
        return true;

    return false;
  }


  /* G is part of the geometric factor */
  double AreaLight::G(const ShadeRec& sr) const {
    double ndotd = -light_normal.dot(wi);
    double d2 = (sample_point - sr.hit_point).squaredNorm();
    return ndotd / d2;
  }


  double AreaLight::pdf(const ShadeRec& sr) const {
    return object_ptr->pdf(sr);
  }
}
