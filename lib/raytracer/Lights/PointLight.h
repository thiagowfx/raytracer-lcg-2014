#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "ShadeRec.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief Represents a point light, having a position, a color and an intensity.
   */
  class PointLight: public Light {
  public:
    PointLight();
    PointLight(const PointLight&);
    virtual Light* clone() const;
    virtual ~PointLight();
    void set_radiance(double);
    void set_color(const RGBColor&);
    void set_location(Vector3d);
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;

  private:
    /** Radiance of light. */
    double ls = 1.0;

    /** Color of light. */
    RGBColor color = white;

    /** Location of light. */
    Vector3d location = Vector3d::Zero();
  };


  inline void PointLight::set_color(const RGBColor& color) {
    this->color = color;
  }


  inline void PointLight::set_location(Vector3d location) {
    this->location = location;
  }


  inline void PointLight::set_radiance(double ls) {
    this->ls = ls;
  }
}

#endif
