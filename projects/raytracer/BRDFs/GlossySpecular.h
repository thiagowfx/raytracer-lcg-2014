#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

/* This implements glossy specular reflection for direct and indirect illumination */
#include "BRDF.h"
#include "MultiJittered.h"

class GlossySpecular: public BRDF {
  
 public:
  GlossySpecular();
  ~GlossySpecular();
  virtual GlossySpecular* clone() const;
  virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
  void set_ks(const float ks);
  void set_exp(const float exp);
  void set_cs(const RGBColor& c);
  void set_sampler(Sampler* sp, const float exp); // any type of sampling
  void set_samples(const int num_samples, const float exp); // multi jittered sampling
  void set_normal(const Vector3d& n);

 private:
  float    ks;
  RGBColor cs;                  // specular color
  float    exp;                 // specular exponent
  Sampler* sampler_ptr;         // for use in sample_f
};


inline void GlossySpecular::set_ks(const float k) {
  ks = k;
}

inline void GlossySpecular::set_exp(const float e) {
  exp = e;
}


inline void GlossySpecular::set_cs(const RGBColor& c) {
  cs = c;
}


#endif
