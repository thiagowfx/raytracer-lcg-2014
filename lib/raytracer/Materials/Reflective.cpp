#include "Reflective.h"

namespace Raytracer {

  Reflective::Reflective() :
    Phong(white) {
    set_ka(0.0);
    set_kd(0.0);
    set_ks(0.0);
    set_cr(white);
  }

  Reflective::Reflective (const RGBColor& color) :
    Phong(color){
    set_cd(color);
    set_cs(color);
    set_cr(color);
  }


  Reflective::Reflective(const Reflective& rm) :
    Phong(rm) {
    if(rm.reflective_brdf)
      reflective_brdf = rm.reflective_brdf->clone();
    else
      reflective_brdf = NULL;
  }


  Reflective* Reflective::clone() const {
    return new Reflective(*this);
  }


  Reflective::~Reflective() {
    if (reflective_brdf) {
      delete reflective_brdf;
      reflective_brdf = NULL;
    }
  }


  bool Reflective::operator==(const Reflective& o) const {
    return
      Phong::operator==(o) &&
      *reflective_brdf == *(o.reflective_brdf);
  }


  RGBColor Reflective::shade(ShadeRec& sr) {
    /* Direct illumination. */
    RGBColor L(Phong::shade(sr));

    Vector3d wo = -sr.ray.direction;
    Vector3d wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);
    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal.dot(wi));
    return L;
  }


  RGBColor Reflective::area_light_shade(ShadeRec& sr) {
    /* Direct illumination. Area light included here. */
    RGBColor L(Phong::area_light_shade(sr));

    Vector3d wo = -sr.ray.direction;
    Vector3d wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);
    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal.dot(wi));
    return L;
  }
}
