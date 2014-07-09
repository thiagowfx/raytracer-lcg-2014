#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "World.h"

namespace Raytracer {
  class Emissive: public Material {

  public:
    Emissive();
    Emissive(const Emissive&);
    virtual Material* clone() const;
    Emissive& operator= (const Emissive&);
    ~Emissive();
    void scale_radiance(const float);
    void set_ce(const RGBColor&);
    virtual RGBColor get_Le(ShadeRec&) const;
    virtual RGBColor shade(ShadeRec&);
    virtual RGBColor area_light_shade(ShadeRec&);
    virtual RGBColor get_color() const;
    static Emissive* generic(RGBColor,double radiance);
  private:
    /* these are an analogy to lights */
    float ls;                   // radiance scaling facor
    RGBColor ce;                // color
  };


  inline void Emissive::scale_radiance(const float ls) {
    this->ls = ls;
  }


  inline void Emissive::set_ce(const RGBColor& c) {
    ce = c;
  }
}

#endif
