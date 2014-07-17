#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief A emissive material makes an object act as a light source,
   * useful for the AreaLighting tracer.
   */
  class Emissive: public Material {
  public:
    Emissive();
    Emissive(const Emissive&);
    virtual Material* clone() const;
    ~Emissive();
    static Emissive* generic(RGBColor,double radiance);
    
    virtual RGBColor get_color() const;
    virtual RGBColor shade(ShadeRec&);

    /* Setters. */
    void set_radiance(const double);
    void set_ce(const RGBColor&);
    
    virtual RGBColor get_Le(ShadeRec&) const;
    virtual RGBColor area_light_shade(ShadeRec&);
  private:
    /** Light radiance (analogy)> */
    double ls = 1.0; 
    /** Light color (analogy). */
    RGBColor ce = white;
  };


  inline void Emissive::set_radiance(const double ls) {
    this->ls = ls;
  }


  inline void Emissive::set_ce(const RGBColor& c) {
    ce = c;
  }
}

#endif
