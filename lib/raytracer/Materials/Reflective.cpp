#include "Reflective.h"

namespace Raytracer {
  Reflective::Reflective () :
    Phong()
  {}


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

  Reflective *Reflective::generic(RGBColor color) {
    Reflective* r = new Reflective();
    r->set_ka(kKa);
    r->set_kd(kKd);
    r->set_cd(color);
    r->set_ks(kKs);
    r->set_cs(color);
    r->set_exp(kExp);
    r->set_kr(kKr);
    r->set_cr(color);
    return r;
  }


  Reflective *Reflective::generic_uncolored() {
    Reflective* r = new Reflective();
    r->set_ka(0.0);
    r->set_kd(0.0);
    r->set_cd(white);
    r->set_ks(0.0);
    r->set_cs(white);
    r->set_exp(kExp);
    r->set_kr(kKr);
    r->set_cr(white);
    return r;
  }
}
