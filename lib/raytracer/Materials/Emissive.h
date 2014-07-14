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
    ~Emissive();
    void set_radiance(const double);
    void set_ce(const RGBColor&);
    virtual RGBColor get_Le(ShadeRec&) const;
    virtual RGBColor shade(ShadeRec&);
    virtual RGBColor area_light_shade(ShadeRec&);
    virtual RGBColor get_color() const;
    static Emissive* generic(RGBColor,double radiance);
  private:
    /* these are an analogy to lights */
    double ls = 1.0; // radiance scaling facor
    RGBColor ce = white; // color
  };


  inline void Emissive::set_radiance(const double ls) {
    this->ls = ls;
  }


  inline void Emissive::set_ce(const RGBColor& c) {
    ce = c;
  }
}

#endif
