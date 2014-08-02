#include "EnvironmentLight.h"

namespace Raytracer {
  EnvironmentLight::EnvironmentLight() :
    Light() {
    this->set_sampler(new MultiJittered(20));
  }


  EnvironmentLight::EnvironmentLight(const EnvironmentLight& el) :
    Light(el),
    u(el.u),
    v(el.v),
    w(el.w),
    wi(el.wi) {
    if(el.sampler_ptr) {
      sampler_ptr = el.sampler_ptr->clone();
    }
    else {
      sampler_ptr = NULL;
    }

    if(el.material_ptr) {
      material_ptr = el.material_ptr->clone();
    }
    else {
      material_ptr = NULL;
    }
  }


  Light* EnvironmentLight::clone() const {
    return new EnvironmentLight(*this);
  }


  EnvironmentLight::~EnvironmentLight() {
    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }
    if (material_ptr) {
      delete material_ptr;
      material_ptr = NULL;
    }
  }


  Vector3d EnvironmentLight::get_direction(ShadeRec& sr) {
    w = sr.normal;
    v = (Vector3d(0.0034, 1, 0.0071).cross(w)).normalized();
    u = v.cross(w);
    Vector3d sp = sampler_ptr->sample_hemisphere();
    wi = sp(0) * u + sp(1) * v + sp(2) * w;
    return wi;
  }


  void EnvironmentLight::set_sampler(Sampler* sampler_ptr) {
    if (this->sampler_ptr) {
      delete this->sampler_ptr;
      this->sampler_ptr = NULL;
    }
    this->sampler_ptr = sampler_ptr;
    this->sampler_ptr->map_samples_to_hemisphere(1);
  }


  RGBColor EnvironmentLight::L(ShadeRec& sr) {
    return material_ptr->get_Le(sr);
  }


  bool EnvironmentLight::in_shadow(const Ray& ray, ShadeRec& sr) const {
    double t;
    const unsigned num_objects = sr.w.objects.size();
    for (unsigned j = 0; j < num_objects; j++)
      if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr))
        return true;
    return false;
  }


  double EnvironmentLight::pdf(const ShadeRec& sr) const {
    return sr.normal.dot(wi) * INV_PI;
  }
}
