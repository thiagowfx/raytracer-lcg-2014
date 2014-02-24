#include "BRDF.h"

BRDF::BRDF() {}


BRDF::BRDF(const BRDF& brdf) {}	


BRDF& BRDF::operator= (const BRDF& rhs) {
  return *this;
}


BRDF::~BRDF() {}  


RGBColor BRDF::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
  return black;
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const {
  return black;
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const {
  return black;
}


RGBColor BRDF::rho(const ShadeRec& sr, const Vector3d& wo) const {
  return black;
}
