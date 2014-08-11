#ifndef _DIRECTIONALLIGHT_MINE_
#define _DIRECTIONALLIGHT_MINE_

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

namespace Raytracer {
  /**
   * @brief Represents a directional light, having a direction, a color and an intensity.
   */
  class DirectionalLight: public Light {
  public:
    /** Create a Directional Light with the specified direction. */
    DirectionalLight(const Vector3d&);
    DirectionalLight(const DirectionalLight&);
    DirectionalLight();
    virtual ~DirectionalLight();
    virtual Light* clone() const;
    virtual bool operator==(const DirectionalLight&) const;

    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;

    /* Setters. */
    void set_radiance(const double);
    void set_color(const RGBColor);
    void set_direction(const Vector3d&);

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Light);
      ar & BOOST_SERIALIZATION_NVP(ls);
      ar & BOOST_SERIALIZATION_NVP(color);
      ar & BOOST_SERIALIZATION_NVP(direction);
    }

  private:
    /** Radiance of light. */
    double ls = 1.0;
    /** Color of light. */
    RGBColor color = white;
    /** Direction of light. */
    Vector3d direction = Vector3d(1.0, 0.0, 0.0);
  };


  inline void DirectionalLight::set_radiance(const double ls) {
    this->ls = ls;
  }


  inline void DirectionalLight::set_color(const RGBColor color) {
    this->color = color;
  }


  inline void DirectionalLight::set_direction(const Vector3d& direction) {
    this->direction = direction;
  }
}

#endif // _DIRECTIONALLIGHT_MINE_
