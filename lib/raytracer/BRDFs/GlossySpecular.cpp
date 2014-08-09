#include "GlossySpecular.h"

namespace Raytracer {
  GlossySpecular::GlossySpecular() :
    BRDF()
  {}


  GlossySpecular::GlossySpecular(const GlossySpecular &gloss) :
    BRDF(gloss),
    ks(gloss.ks),
    cs(gloss.cs),
    exp(gloss.exp) {}

  GlossySpecular* GlossySpecular::clone () const {
    return new GlossySpecular(*this);
  }


  GlossySpecular::~GlossySpecular() {}


  bool GlossySpecular::operator==(const GlossySpecular& o) const {
    return
      BRDF::operator==(o) &&
      ks == o.ks &&
      exp == o.exp &&
      cs == o.cs;
  }


  RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
    RGBColor L;
    double ndotwi = sr.normal.dot(wi);
    Vector3d r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
    double rdotwo = r.dot(wo);
    if (rdotwo > 0.0) {
      L = ks * cs * pow(rdotwo, exp);
    }
    return L;
  }


  RGBColor GlossySpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
    double ndotwo = sr.normal.dot(wo);
    Vector3d r = -wo + (2.0 * sr.normal * ndotwo); // direction of mirror reflection
    Vector3d w = r;
    Vector3d u = Vector3d(0.00424, 1.0, 0.00764).cross(w).normalized();
    Vector3d v = u.cross(w);
    Vector3d sp = sampler_ptr->sample_hemisphere();
    wi = (sp(0) * u) + (sp(1) * v) + (sp(2) * w); // reflected ray direction

    if (sr.normal.dot(wi) < 0.0) {    // reflected ray is below tangent plane
      wi = (-sp(0) * u) - (sp(1) * v) + (sp(2) * w);
    }

    double phong_lobe = pow(r.dot(wi), exp);
    pdf = phong_lobe * (sr.normal.dot(wi));
    return ks * cs * phong_lobe;
  }
}
