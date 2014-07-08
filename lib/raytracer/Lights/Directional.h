#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

namespace Raytracer {
  /**
   * @brief Represents a directional light, having a direction, a color and an intensity.
   */
  class Directional: public Light {
  public:
    Directional();
    Directional(const Directional& dl);
    virtual Light* clone() const;
    virtual ~Directional();
    void scale_radiance(const double b);
    void set_color(const RGBColor&);
    void set_direction(Vector3d);
    virtual Vector3d get_direction(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);
    virtual bool in_shadow(const Ray& ray, ShadeRec& sr) const;
  private:
    /** Radiance of light. */
    double ls = 1.0;
    
    /** Color of light. */
    RGBColor color = white;
    
    /** Direction of light. */
    Vector3d direction = Vector3d(0.0, 1.0, 0.0);
  };


  inline void Directional::scale_radiance(const double ls) {
    this->ls = ls;
  }


  inline void Directional::set_color(const RGBColor& color) {
    this->color = color;
  }

  
  inline void Directional::set_direction(Vector3d d) {
    direction = d;
    direction.normalize();
  }
}

#endif
