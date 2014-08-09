#include "PerfectSpecular.h"

namespace Raytracer {
  PerfectSpecular::PerfectSpecular() :
    BRDF()
  {}


  PerfectSpecular::PerfectSpecular(const PerfectSpecular& ps) :
    BRDF(ps),
    kr(ps.kr),
    cr(ps.cr)
  {}


  PerfectSpecular* PerfectSpecular::clone() const {
    return new PerfectSpecular(*this);
  }


  PerfectSpecular::~PerfectSpecular() {}


  bool PerfectSpecular::operator==(const PerfectSpecular& o) const {
    return
      BRDF::operator==(o) &&
      kr == o.kr &&
      cr == o.cr;
  }


  RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const {
    double ndotwo = sr.normal.dot(wo);
    wi = -wo + (2.0 * sr.normal * ndotwo);
    return kr * cr / (sr.normal.dot(wi));
  }


  RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
    double ndotwo = sr.normal.dot(wo);
    wi = -wo + (2.0 * sr.normal * ndotwo);
    pdf = fabs(sr.normal.dot(wi));
    return kr * cr;
  }
}
