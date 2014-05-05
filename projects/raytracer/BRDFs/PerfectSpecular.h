#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

/* this implements perfect specular reflection for indirect illumination with reflective materials */

#include "BRDF.h"

class PerfectSpecular: public BRDF {
  
 public:
  PerfectSpecular();
  ~PerfectSpecular();
  virtual PerfectSpecular* clone() const;
  void set_kr(const double k);
  void set_cr(const RGBColor&);
  void set_cr(double,double,double);
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;
				
 private:
  double kr;			// reflection coefficient
  RGBColor cr;			// the reflection colour  
};


inline void PerfectSpecular::set_kr(const double k) {
  kr = k;
}


inline void PerfectSpecular::set_cr(const RGBColor& c) {
  cr = c;
}


inline void PerfectSpecular::set_cr(double r, double g, double b) {
  cr.r = r;
  cr.g = g;
  cr.b = b;
}


#endif

