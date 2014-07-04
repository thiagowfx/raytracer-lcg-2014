#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "GlossySpecular.h"
#include "Lambertian.h"
#include "World.h"

namespace Raytracer {
  class Phong : public Material {

  public:
    Phong();
    Phong(const Phong& m);
    virtual Material* clone() const;
    virtual ~Phong();
    void set_ka(double ka);
    void set_cd(const RGBColor& color);
    void set_kd(double kd);
    void set_cs(const RGBColor& color);
    void set_ks(double ks);
    void set_exp(double exp);
    virtual RGBColor shade (ShadeRec& s);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    static Phong* dummy(RGBColor);
    virtual RGBColor get_color() const;

  private:
    Lambertian *ambient_brdf;
    Lambertian *diffuse_brdf;
    GlossySpecular *specular_brdf;
  };

  inline void Phong::set_ka (double ka) {
    ambient_brdf->set_kd(ka);
  }

  inline void Phong::set_kd (double kd) {
    diffuse_brdf->set_kd(kd);
  }

  inline void Phong::set_ks (double ks) {
    specular_brdf->set_ks(ks);
  }

  inline void Phong::set_cd (const RGBColor& color) {
    ambient_brdf->set_cd(color);
    diffuse_brdf->set_cd(color);
    specular_brdf->set_cs(color);
  }

  inline void Phong::set_exp (double exp) {
    specular_brdf->set_exp(exp);
  }

  inline void Phong::set_cs(const RGBColor& color) {
    specular_brdf->set_cs(color);
  }
}

#endif
