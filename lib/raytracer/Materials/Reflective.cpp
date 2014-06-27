#include "Reflective.h"

Reflective::Reflective () :
  Phong(),
  reflective_brdf(new PerfectSpecular)
{}


Reflective::Reflective(const Reflective& rm) :
  Phong(rm),
  reflective_brdf(NULL)
{	
  if(rm.reflective_brdf)
    reflective_brdf = rm.reflective_brdf->clone(); 
}


Reflective& Reflective::operator= (const Reflective& rhs) {
  if (this != &rhs) {		
    Phong::operator=(rhs);
    if (reflective_brdf) {
      delete reflective_brdf;
      reflective_brdf = NULL;
    }

    if (rhs.reflective_brdf)
      reflective_brdf = rhs.reflective_brdf->clone();
  }
  return *this;
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
  RGBColor L(Phong::shade(sr)); // direct illumination
	
  Vector3d wo = -sr.ray.d;
  Vector3d wi;	
  RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
  Ray reflected_ray(sr.hit_point, wi);
  L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal.dot(wi));
					
  return L;
}

/** Has direct illumination */
Reflective *Reflective::dummy(RGBColor color) {
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


/** Doesn't have direct illumination */
Reflective *Reflective::nodirect(RGBColor color) {
  Reflective* r = new Reflective();
  r->set_ka(0.0);
  r->set_kd(0.0);
  r->set_cd(color);
  r->set_ks(0.0);
  r->set_cs(color);
  r->set_exp(kExp);
  r->set_kr(kKr);
  r->set_cr(color);
  return r;
}


/** Black-ish, just the reflections */
Reflective *Reflective::uncolored() {
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
