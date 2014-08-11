#ifndef _LIGHT_MINE_
#define _LIGHT_MINE_

#include "BoostMine.hpp"
#include "Utilities.h"
#include "Ray.h"
#include "RGBColor.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  class ShadeRec;
  /**
   * @brief A light gives illumination to world objects.
   */
  class Light {
  public:
    Light();
    Light(const Light&);
    virtual Light* clone() const = 0;
    virtual ~Light();
    virtual bool operator==(const Light&) const;

    /** Get the direction defined by two points: hit point and light point. */
    virtual Vector3d get_direction(ShadeRec&) = 0;

    /** Test if the given ray hits the light -- is there an object between the ray origin and the light? */
    virtual bool in_shadow(const Ray&, ShadeRec&) const = 0;

    /** Radiance (color + intensity) that this light emits, affects shading of objects. */
    virtual RGBColor L(ShadeRec&) = 0;

    /** Does this light cast shadows? */
    bool get_shadows() const;

    /** Sets the shadow property of this light. */
    void set_shadows(const bool);

    /* For area lights.  Default value for both of them is 1.0, allowing
       us to add point and directional lights to scenes with area
       lights. */
    virtual double G(const ShadeRec&) const;
    virtual double pdf(const ShadeRec&) const;

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(shadows);
    }

  protected:
    /** Does this light cast shadows? */
    bool shadows = true;
  };
}

#endif // _LIGHT_MINE_
