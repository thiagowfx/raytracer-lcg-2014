#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.h"

class Lambertian: public BRDF {
  
 public:
  Lambertian();
  Lambertian(const Lambertian& lamb);
  virtual Lambertian* clone() const;
  ~Lambertian();
  Lambertian& operator= (const Lambertian& rhs);
  virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;
  void set_kd(double);
  void set_cd(const RGBColor&);
  void set_cd(double,double,double);
  double get_kd() const;
  RGBColor get_cd() const;
					
 private:
  double kd;
  RGBColor cd;  
};


inline void Lambertian::set_kd(double k) {
  kd = k;
}


inline void Lambertian::set_cd(const RGBColor& color) {
  cd = color;
}


inline void Lambertian::set_cd(double r, double g, double b) {
  cd.r = r;
  cd.g = g;
  cd.b = b;
}


inline double Lambertian::get_kd() const {
  return kd;
}


inline RGBColor Lambertian::get_cd() const {
  return cd;
}

#endif
