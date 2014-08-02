#ifndef _BRDF_MINE_
#define _BRDF_MINE_

#include "RGBColor.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include "MultiJittered.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief An abstraction/model for shading calculations.
   */
  class BRDF {
  public:
    BRDF();
    ~BRDF();
    BRDF(const BRDF&);
    virtual BRDF* clone() const = 0;

    /* Setters. */
    /** Set a sampler for this BRDF. Currently only useful for
	GlossySpecular. Set number of samples to 1 for perfect
	diffuse. */
    void set_sampler(Sampler*, const double exp);
   
    /** Used to compute the direction of reflected rays for simulating
	reflective materials and diffuse-diffuse light transport. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi) const;
    /** Used to compute the direction of reflected rays for simulating
	reflective materials and diffuse-diffuse light
	transport. This version is for area lights. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    /** The BRDF itself. For example, this is /pi for a lambertian. */
    virtual RGBColor f(const ShadeRec&, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor rho(const ShadeRec&, const Vector3d& wo) const;
  protected:
    /** Sampler for indirect illumination. */
    Sampler* sampler_ptr = NULL;
  };
}

#endif // _BRDF_MINE_
