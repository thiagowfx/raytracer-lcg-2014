#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief A emissive material makes an object act as a light source,
   * being useful for the AreaLighting tracer. Doesn't reflect
   * light. Only emits light on a single side of the object.
   */
  class Emissive: public Material {
  public:
    /** Construct a new Emissive material with the given color and radiance. */
    Emissive(const RGBColor&, double radiance = 1.0);
    Emissive(const Emissive&);
    virtual Material* clone() const;
    ~Emissive();
    
    virtual RGBColor get_color() const;
    /** Allow this object to be rendered with tracers other than
	AreaLighting ones. Same as area_light_shade. */
    virtual RGBColor shade(ShadeRec&);

    /* Setters. */
    /** Set radiance of this emissive material. */
    void set_radiance(const double);
    /** Set light color of this emissive material. */
    void set_ce(const RGBColor&);

    /** The effective color (radiance * hue) emitted by this material. */
    virtual RGBColor get_Le(ShadeRec&) const;
    /** Allow this object to be rendered with tracers other than
	AreaLighting ones. Same as shade. */
    virtual RGBColor area_light_shade(ShadeRec&);
  private:
    /** Light radiance (analogy) */
    double ls = 1.0; 
    /** Light color (analogy). */
    RGBColor ce = white;
  };


  inline void Emissive::set_radiance(const double ls) {
    this->ls = ls;
  }


  inline void Emissive::set_ce(const RGBColor& ce) {
    this->ce = ce;
  }
}

#endif
