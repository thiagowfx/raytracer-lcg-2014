#include "GlossySpecular.h"

GlossySpecular::GlossySpecular() :
  ks(0.0),
  cs(RGBColor(1.0, 1.0, 1.0)),
  sampler(NULL)
{}


GlossySpecular* GlossySpecular::clone () const {
  return new GlossySpecular(*this);
}


GlossySpecular::~GlossySpecular() {}


/* this allows any type of sampling to be specified in the build functions */
void GlossySpecular::set_sampler(Sampler* sp, const float exp) {
  sampler_ptr = sp;
  sampler_ptr->map_samples_to_hemisphere(exp);
}


/* this sets up multi-jittered sampling using the number of samples */
void GlossySpecular::set_samples(const int num_samples, const float exp) {
  sampler_ptr = new MultiJittered(num_samples);
  sampler_ptr->map_samples_to_hemisphere(exp);
}


/* no sampling here: just use the Phong formula
   this is used for direct illumination only */
RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const {
  RGBColor L;
  float ndotwi = sr.normal.dot(wi);
  Vector3d r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
  float rdotwo = r.dot(wo);

  if (rdotwo > 0.0)
    L = ks * cs * pow(rdotwo, exp);

  return L;
}


/* this is used for indirect illumination */
RGBColor GlossySpecular::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const {
  float ndotwo = sr.normal.dot(wo);
  Vector3d r = -wo + (2.0 * sr.normal * ndotwo); // direction of mirror reflection
  Vector3d w = r;
  Vector3d u = Vector3d(0.00424, 1, 0.00764).cross(w);
  u.normalize();
  Vector3d v = u.cross(w);
  Vector3d sp = sampler_ptr->sample_hemisphere();
  wi = (sp(0) * u) + (sp(1) * v) + (sp(2) * w); // reflected ray direction

  if (sr.normal.dot(wi) < 0.0)    // reflected ray is below tangent plane
    wi = (-sp(0) * u) - (sp(1) * v) + (sp(2) * w);

  float phong_lobe = pow(r.dot(wi), exp);
  pdf = phong_lobe * (sr.normal.dot(wi));

  return ks * cs * phong_lobe;
}


RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3d& wo) const {
  return RGBColor();
}