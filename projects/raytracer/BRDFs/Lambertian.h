#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.h"
#include "Constants.h"

class Lambertian: public BRDF {
  
 public:
  Lambertian();
  Lambertian(const Lambertian& lamb);
  virtual Lambertian* clone() const;
  ~Lambertian();
  Lambertian& operator= (const Lambertian& rhs);
  virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
  void set_ka(const float ka);	
  void set_kd(const float kd);
  void set_cd(const RGBColor& c);
					
 private:
  float	   kd;
  RGBColor cd;
  
};


inline void Lambertian::set_ka(const float k) {
  kd = k;
}


inline void Lambertian::set_kd(const float k) {
  kd = k;
}


inline void Lambertian::set_cd(const RGBColor& c) {
  cd = c;
}


#endif
