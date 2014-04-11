#ifndef __BRDF__
#define __BRDF__

#include "RGBColor.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class BRDF {
  
 public:	
  BRDF();						
  BRDF(const BRDF& object);
  virtual BRDF* clone() const = 0;
  ~BRDF();
  void set_sampler(Sampler* sPtr);
  virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
		
 protected:
  BRDF& operator= (const BRDF& rhs);
  Sampler* sampler_ptr;         // for indirect illumination
};


#endif