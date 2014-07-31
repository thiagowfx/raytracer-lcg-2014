#ifndef _POINTLIGHT_MINE_
#define _POINTLIGHT_MINE_

#include "Light.h"
#include "ShadeRec.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief Represents a point light, having a location, a color and an intensity.
   */
  class PointLight: public Light {
  public:
    /** Create a point light at the specified location. */
    PointLight(const Vector3d);
    PointLight(const PointLight&);
    virtual Light* clone() const;
    virtual ~PointLight();

    virtual Vector3d get_direction(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;
    virtual RGBColor L(ShadeRec&);

    /* Setters. */
    void set_radiance(double);
    void set_color(const RGBColor);
  private:
    /** Radiance of light. */
    double ls = 1.0;
    /** Color of light. */
    RGBColor color = white;
    /** Location of light. */
    Vector3d location = Vector3d::Zero();
  };


  inline void PointLight::set_color(const RGBColor color) {
    this->color = color;
  }


  inline void PointLight::set_radiance(double ls) {
    this->ls = ls;
  }
}

#endif // _POINTLIGHT_MINE_
