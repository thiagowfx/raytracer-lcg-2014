#ifndef _PERFECTSPECULAR_MINE_
#define _PERFECTSPECULAR_MINE_

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

    /** This computes wi: the direction of perfect mirror reflection
     * it's called from from the functions Reflective::shade and
     * Transparent::shade.  the fabs in the last statement is for
     * transparency. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi) const;
    /** This version of sample_f is used with path tracing it returns
     ndotwi in the pdf. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;
  private:
    /** Reflection coefficient constant. */
    double kr = kKr;
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

#endif // _PERFECTSPECULAR_MINE_
