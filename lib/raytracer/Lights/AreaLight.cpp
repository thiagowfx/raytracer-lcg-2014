#include "AreaLight.h"

namespace Raytracer {
  AreaLight::AreaLight() :
    Light()
  {}


  AreaLight::AreaLight(const AreaLight& al) :
    Light(al) {
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


  Vector3d AreaLight::get_direction(ShadeRec& sr) {
    sample_point = object_ptr->sample();
    light_normal = object_ptr->get_normal(sample_point);
    return wi = (sample_point - sr.hit_point).normalized();
  }


  RGBColor AreaLight::L(ShadeRec& sr) {
    double ndotd = -light_normal.dot(wi);
    if (ndotd > 0.0) {
      return (material_ptr->get_Le(sr));
    }
    else {
      return black;
    }
  }


  bool AreaLight::in_shadow(const Ray& ray, ShadeRec& sr) const {
    double t;
    const unsigned num_objects = sr.w.objects.size();
    double ts = (sample_point - ray.origin).dot(ray.direction);
    for (unsigned j = 0; j < num_objects; ++j) {
      if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr) && t < ts) {
        return true;
      }
    }
    return false;
  }


  double AreaLight::G(const ShadeRec& sr) const {
    double ndotd = -light_normal.dot(wi);
    double d2 = (sample_point - sr.hit_point).squaredNorm();
    return ndotd / d2;
  }


  double AreaLight::pdf(const ShadeRec& sr) const {
    return object_ptr->pdf(sr);
  }
}
