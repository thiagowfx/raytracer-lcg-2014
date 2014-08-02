#include "Lambertian.h"

namespace Raytracer {
  Lambertian::Lambertian() :
    BRDF()
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


  RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
    Vector3d w = sr.normal;
    Vector3d v = Vector3d(0.0034, 1.0, 0.0071).cross(w);
    v.normalize();
    Vector3d u = v.cross(w);

    Vector3d sp = sampler_ptr->sample_hemisphere();
    wi = (sp(0) * u) + (sp(1) * v) + (sp(2) * w);
    wi.normalize();

    pdf = sr.normal.dot(wi) * INV_PI;
    return kd * cd * INV_PI;
  }


  RGBColor Lambertian::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
    return kd * cd * INV_PI;
  }


  RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3d& wo) const {
    return kd * cd;
  }
}
