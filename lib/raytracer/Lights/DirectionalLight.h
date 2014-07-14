#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

namespace Raytracer {
  /**
   * @brief Represents a directional light, having a direction, a color and an intensity.
   */
  class DirectionalLight: public Light {
  public:
    DirectionalLight();
    DirectionalLight(const DirectionalLight&);
    virtual Light* clone() const;
    virtual ~DirectionalLight();
    void scale_radiance(const double);
    void set_color(const RGBColor&);
    void set_direction(Vector3d);
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;
  private:
    /** Radiance of light. */
    double ls = 1.0;
    
    /** Color of light. */
    RGBColor color = white;
    
    /** Direction of light. */
    Vector3d direction = Vector3d(0.0, 1.0, 0.0);
  };


  inline void DirectionalLight::scale_radiance(const double ls) {
    this->ls = ls;
  }


  inline void DirectionalLight::set_color(const RGBColor& color) {
    this->color = color;
  }

  
  inline void DirectionalLight::set_direction(Vector3d d) {
    direction = d.normalized();
  }
}

#endif
