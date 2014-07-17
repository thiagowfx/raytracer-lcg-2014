#ifndef _MATTE_MINE_
#define _MATTE_MINE_

#include "Material.h"
#include "Lambertian.h"
#include "World.h"

namespace Raytracer {
  class Matte: public Material {
  public:
    Matte();
    ~Matte();
    Matte(const Matte&);
    virtual Material* clone() const;
    static Matte* generic(RGBColor);
    
    virtual RGBColor get_color() const;
    virtual RGBColor shade(ShadeRec&);

    /* Setters. */
    void set_ka(const double);
    void set_kd(const double);
    void set_cd(const RGBColor&);
    
    virtual RGBColor area_light_shade(ShadeRec&);

  private:
    /** Ambient color component. */
    Lambertian* ambient_brdf = new Lambertian();
    /** Diffuse color component. */
    Lambertian* diffuse_brdf = new Lambertian();
  };

  /** This sets Lambertian::kd, there is no Lambertian::ka data member
      because ambient reflection is diffuse reflection */
  inline void Matte::set_ka(const double ka) {
    ambient_brdf->set_kd(ka);
  }

  
  /** This also sets Lambertian::kd, but for a different Lambertian
     object */
  inline void Matte::set_kd(const double kd) {
    diffuse_brdf->set_kd(kd);
  }


  inline void Matte::set_cd(const RGBColor& c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
  }
}

#endif // _MATTE_MINE_
