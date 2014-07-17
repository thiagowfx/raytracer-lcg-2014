#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

#include "BRDF.h"

namespace Raytracer {
  /**
   * @brief Perfect specular reflection for indirect illumination with reflective materials.
   */
  class PerfectSpecular: public BRDF {
  public:
    PerfectSpecular();
    ~PerfectSpecular();
    PerfectSpecular(const PerfectSpecular&);
    virtual PerfectSpecular* clone() const;

    /* Setters. */
    void set_kr(const double);
    void set_cr(const RGBColor&);
    
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;
  private:
    /** Reflection coefficient constant. */
    double kr = 0.0;
    /** Reflection color. */
    RGBColor cr = white;
  };


  inline void PerfectSpecular::set_kr(const double k) {
    kr = k;
  }


  inline void PerfectSpecular::set_cr(const RGBColor& c) {
    cr = c;
  }
}

#endif
