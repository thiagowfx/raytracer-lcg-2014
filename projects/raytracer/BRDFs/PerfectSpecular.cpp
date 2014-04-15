#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular() :
  BRDF(),
  kr(0.0), 
  cr(1.0, 1.0, 1.0)
{}


PerfectSpecular::~PerfectSpecular() {}


PerfectSpecular* PerfectSpecular::clone() const {
  return new PerfectSpecular(*this);
}	


RGBColor PerfectSpecular::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
  return RGBColor();
}


/* this computes wi: the direction of perfect mirror reflection
   it's called from from the functions Reflective::shade and Transparent::shade.
   the fabs in the last statement is for transparency */
RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const {
  double ndotwo = sr.normal.dot(wo);
  wi = -wo + (2.0 * sr.normal * ndotwo);
  return kr * cr / fabs(sr.normal.dot(wi));
}


/* this version of sample_f is used with path tracing
   it returns ndotwi in the pdf */
RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
  double ndotwo = sr.normal.dot(wo);
  wi = -wo + (2.0 * sr.normal * ndotwo);
  pdf = fabs(sr.normal.dot(wi));
  return kr * cr;
}


RGBColor PerfectSpecular::rho(const ShadeRec& sr, const Vector3d& wo) const {
  return RGBColor();
}
