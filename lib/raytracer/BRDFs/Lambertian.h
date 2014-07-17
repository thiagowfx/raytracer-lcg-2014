#ifndef _LAMBERTIAN_MINE
#define _LAMBERTIAN_MINE

#include "BRDF.h"

namespace Raytracer {
  class Lambertian: public BRDF {
  public:
    Lambertian();
    Lambertian(const Lambertian&);
    virtual Lambertian* clone() const;
    ~Lambertian();
    
    virtual RGBColor f(const ShadeRec& sr, const Vector3d& wo, const Vector3d& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3d& wo) const;

    /* Setters. */
    void set_kd(double);
    void set_cd(const RGBColor&);

    /* Getters. */
    double get_kd() const;
    RGBColor get_cd() const;
  private:
    /** Diffuse coefficient constant. */
    double kd = 0.0;
    /** Diffuse color. */
    RGBColor cd = black;
  };


  inline void Lambertian::set_kd(double k) {
    this->kd = k;
  }


  inline void Lambertian::set_cd(const RGBColor& color) {
    this->cd = color;
  }


  inline double Lambertian::get_kd() const {
    return kd;
  }


  inline RGBColor Lambertian::get_cd() const {
    return cd;
  }
}

#endif // _LAMBERTIAN_MINE
