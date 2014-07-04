#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "World.h"

namespace Raytracer {
  class Emissive: public Material {

  public:
    Emissive();
    Emissive(const Emissive& m);
    virtual Material* clone() const;
    Emissive& operator= (const Emissive& rhs);
    ~Emissive();
    void scale_radiance(const float _ls);
    void set_ce(const RGBColor& c);
    void set_ce(const float r, const float g, const float b);
    virtual RGBColor get_Le(ShadeRec& sr) const;
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor get_color() const;
    static Emissive* dummy(RGBColor c,double radiance);
  private:
    /* these are an analogy to lights */
    float ls;                   // radiance scaling facor
    RGBColor ce;                // color
  };


  inline void Emissive::scale_radiance(const float _ls) {
    ls = _ls;
  }


  inline void Emissive::set_ce(const float r, const float g, const float b) {
    ce.r = r;
    ce.g = g;
    ce.b = b;
  }


  inline void Emissive::set_ce(const RGBColor &c) {
    ce = c;
  }
}

#endif
