#ifndef __LIGHT__
#define __LIGHT__

#include "Utilities.h"
#include "Ray.h"
#include "RGBColor.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  class ShadeRec;

  class Light {
  public:
    Light();
    Light(const Light&);
    virtual Light* clone() const = 0;
    virtual ~Light();
    virtual Vector3d get_direction(ShadeRec&) = 0;
    virtual RGBColor L(ShadeRec&) = 0; // radiance
    bool get_shadows() const;
    void set_shadows(const bool shadow);
    virtual bool in_shadow(const Ray&, ShadeRec&) const = 0;
    virtual double G(const ShadeRec&) const; /* for area lights */
    virtual double pdf(const ShadeRec&) const; /* for area lights */
  protected:
    bool shadows = true;
  };
}

#endif
