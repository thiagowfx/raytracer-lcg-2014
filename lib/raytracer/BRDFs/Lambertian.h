#ifndef _LAMBERTIAN_MINE_
#define _LAMBERTIAN_MINE_

#include "BRDF.h"

namespace Raytracer {
  class Lambertian: public BRDF {
  public:
    Lambertian();
    Lambertian(const Lambertian&);
    virtual Lambertian* clone() const;
    ~Lambertian();
    
    virtual RGBColor f(const ShadeRec&, const Vector3d& wo, const Vector3d& wi) const;
    /** This generates a direction by sampling the hemisphere with a cosine distribution
     * this is called in path_shade for any material with a diffuse shading component
     * the samples have to be stored with a cosine distribution. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;
    /** Overall color = constant * hue */
    virtual RGBColor rho(const ShadeRec&, const Vector3d& wo) const;

    /* Setters. */
    void set_kd(double);
    void set_cd(const RGBColor&);

    /* Getters. */
    double get_kd() const;
    RGBColor get_cd() const;
  private:
    /** Diffuse coefficient constant. */
    double kd = kKd;
    /** Diffuse color. */
    RGBColor cd = white;
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

#endif // _LAMBERTIAN_MINE_
