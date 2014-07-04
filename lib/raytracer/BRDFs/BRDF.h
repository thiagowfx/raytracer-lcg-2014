#ifndef __BRDF__
#define __BRDF__

#include "RGBColor.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  class BRDF {
  public:
    BRDF();
    BRDF(const BRDF& object);
    virtual BRDF* clone() const = 0;
    BRDF& operator= (const BRDF& rhs);
    ~BRDF();
    void set_sampler(Sampler* sPtr);
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;

  protected:
    Sampler* sampler_ptr = NULL;        // for indirect illumination
  };
}

#endif
