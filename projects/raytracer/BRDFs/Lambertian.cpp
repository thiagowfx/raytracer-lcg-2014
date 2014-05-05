#include "Lambertian.h"

Lambertian::Lambertian() :
  BRDF(),
  kd(0.0),
  cd(0.0, 0.0, 0.0)
{}


Lambertian::Lambertian(const Lambertian& lamb) :
  BRDF(lamb),
  kd(lamb.kd),
  cd(lamb.cd)
{}


Lambertian* Lambertian::clone() const {
  return new Lambertian(*this);
}


Lambertian::~Lambertian() {}


Lambertian& Lambertian::operator= (const Lambertian& rhs) {
  if (this != &rhs) {
    BRDF::operator= (rhs);
    kd = rhs.kd;
    cd = rhs.cd;
  }
  return *this;
}


/* this generates a direction by sampling the hemisphere with a cosine distribution
   this is called in path_shade for any material with a diffuse shading component
   the samples have to be stored with a cosine distribution */
RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
  Vector3d w = sr.normal;
  Vector3d v = Vector3d(0.0034, 1.0, 0.0071).cross(w);
  v.normalize();
  Vector3d u = v.cross(w);

  Vector3d sp = sampler_ptr->sample_hemisphere();
  wi = (sp(0) * u) + (sp(1) * v) + (sp(2) * w);
  wi.normalize();

  pdf = sr.normal.dot(wi) * (1 / M_PI);
  return kd * cd * (1 / M_PI);
}


/** Chapter 14 */
RGBColor Lambertian::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
  return kd * cd * (1 / M_PI);
}


/** Chapter 14: overall color = constant * hue */
RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3d& wo) const {
  return kd * cd;
}
