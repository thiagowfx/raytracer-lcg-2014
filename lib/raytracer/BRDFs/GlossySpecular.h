#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

/* This implements glossy specular reflection for direct and indirect illumination */
#include "BRDF.h"
#include "MultiJittered.h"

namespace Raytracer {
  class GlossySpecular: public BRDF {

  public:
    GlossySpecular();
    GlossySpecular(const GlossySpecular& gloss);
    ~GlossySpecular();
    virtual GlossySpecular* clone() const;
    virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    void set_ks(const double ks);
    void set_exp(const double exp);
    void set_cs(const RGBColor&);
    void set_cs(double,double,double);
    void set_sampler(Sampler* sp, const double exp); // any type of sampling
    void set_samples(const int num_samples, const double exp); // multi jittered sampling
    void set_normal(const Vector3d& n);

  private:
    double ks;
    RGBColor cs;               // specular color
    double exp;                // specular exponent (e)
    Sampler* sampler;          // for use in sample_f
  };


  inline void GlossySpecular::set_ks(const double k) {
    ks = k;
  }


  inline void GlossySpecular::set_exp(const double e) {
    exp = e;
  }


  inline void GlossySpecular::set_cs(const RGBColor& c) {
    cs = c;
  }


  inline void GlossySpecular::set_cs(double r, double g, double b) {
    cs.r = r;
    cs.g = g;
    cs.b = b;
  }
}

#endif
