#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "Lambertian.h"
#include "World.h"

namespace Raytracer {
  class Matte: public Material {

  public:
    Matte();
    Matte(const Matte& m);
    virtual Material* clone() const;
    Matte& operator= (const Matte& rhs);
    ~Matte();
    void set_ka(const double k);
    void set_kd(const double k);
    void set_cd(const RGBColor& c);
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    static Matte* dummy(RGBColor);
    virtual RGBColor get_color() const;

  private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
  };

  /* this sets Lambertian::kd,
     there is no Lambertian::ka data member because ambient reflection is diffuse reflection */
  inline void Matte::set_ka(const double ka) {
    ambient_brdf->set_kd(ka);
  }


  /* this also sets Lambertian::kd, but for a different Lambertian object */
  inline void Matte::set_kd(const double kd) {
    diffuse_brdf->set_kd(kd);
  }


  inline void Matte::set_cd(const RGBColor& c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
  }
}

#endif
