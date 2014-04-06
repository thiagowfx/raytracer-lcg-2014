#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

/* this implements perfect specular reflection for indirect illumination with reflective materials */

#include "BRDF.h"

class PerfectSpecular: public BRDF {
  
 public:
  PerfectSpecular();
  ~PerfectSpecular();
  virtual PerfectSpecular* clone() const;
  void set_kr(const float k);
  void set_cr(const RGBColor& c);
  virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
				
 private:
  float	   kr;			// reflection coefficient
  RGBColor cr;			// the reflection colour
  
};


inline void PerfectSpecular::set_kr(const float k) {
  kr = k;
}


inline void PerfectSpecular::set_cr(const RGBColor& c) {
  cr = c;
}


#endif

