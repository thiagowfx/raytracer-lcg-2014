#ifndef _PHONG_MINE_
#define _PHONG_MINE_

#include "Material.h"
#include "GlossySpecular.h"
#include "Lambertian.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief A material that models ambient + diffuse + reflective
   * radiance (suitable for the Phong model of illumination).
   */
  class Phong : public Material {
  public:
    Phong();
    Phong(const Phong&);
    virtual Material* clone() const;
    virtual ~Phong();
    static Phong* generic(RGBColor);
    
    virtual RGBColor get_color() const;
    virtual RGBColor shade(ShadeRec&);
    virtual RGBColor area_light_shade(ShadeRec&);

    /* Setters. */
    void set_ka(double);
    void set_cd(const RGBColor&);
    void set_kd(double);
    void set_cs(const RGBColor&);
    void set_ks(double);
    void set_exp(double);
    
  private:
    /** Ambient color component. */
    Lambertian *ambient_brdf = new Lambertian();
    /** Diffuse color component. */
    Lambertian *diffuse_brdf = new Lambertian();
    /** Reflective color component. */
    GlossySpecular *specular_brdf = new GlossySpecular();
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

#endif // _PHONG_MINE_
