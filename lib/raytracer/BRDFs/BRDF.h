#ifndef _BRDF_MINE_
#define _BRDF_MINE_

#include "RGBColor.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief An abstraction of shading calculations.
   */
  class BRDF {
  public:
    BRDF();
    ~BRDF();
    BRDF(const BRDF& object);
    virtual BRDF* clone() const = 0;
    BRDF& operator= (const BRDF& rhs);

    /* Setters. */
    void set_sampler(Sampler*);
    
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
  protected:
    /** Sampler for indirect illumination. */
    Sampler* sampler_ptr = NULL;
  };
}

#endif // _BRDF_MINE_
