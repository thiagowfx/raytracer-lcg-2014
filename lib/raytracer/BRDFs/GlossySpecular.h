#ifndef _GLOSSYSPECULAR_MINE_
#define _GLOSSYSPECULAR_MINE_

#include "BRDF.h"
#include "MultiJittered.h"

namespace Raytracer {
  /**
   * @brief Glossy specular reflection for direct and indirect illumination.
   */
  class GlossySpecular: public BRDF {
  public:
    GlossySpecular();
    GlossySpecular(const GlossySpecular&);
    ~GlossySpecular();
    virtual GlossySpecular* clone() const;
    
    virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;

    /* Setters. */
    void set_ks(const double);
    void set_exp(const double);
    void set_cs(const RGBColor&);
    void set_sampler(Sampler*, const double exp); // any type of sampling
    void set_samples(const int number_of_samples, const double exp); // multi jittered sampling
    void set_normal(const Vector3d&);

  private:
    /** Specular (reflective) coefficient constant. */
    double ks = 0.0;
    /** Specular (reflective) color. */
    RGBColor cs = white;
    /** Specular exponent constant. */
    double exp = kExp;
    Sampler* sampler = NULL;	// for use in sample_f
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
}

#endif // _GLOSSYSPECULAR_MINE_
