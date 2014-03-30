#include "Reflective.h"

Reflective::Reflective () :
  Phong(),
  reflective_brdf(new PerfectSpecular)
{}


Reflective::Reflective(const Reflective& rm) :
  Phong(rm) {
	
  if(rm.reflective_brdf)
    reflective_brdf = rm.reflective_brdf->clone(); 
  else  
    reflective_brdf = NULL;
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
  // reflected_ray.depth = sr.depth + 1;	
  L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal.dot(wi));
					
  return L;
}
