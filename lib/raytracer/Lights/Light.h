#ifndef __LIGHT__
#define __LIGHT__

#include "Utilities.h"
#include "Ray.h"
#include "RGBColor.h"
#include <Eigen/Dense>
using Eigen::Vector3d;
class ShadeRec;

class Light {

public:
  Light();
  Light(const Light& ls);
  Light& operator= (const Light& rhs);
  virtual Light* clone() const = 0;
  virtual ~Light();
  virtual Vector3d get_direction(ShadeRec&) = 0;
  virtual RGBColor L(ShadeRec& sr) = 0; // radiance
  bool casts_shadows() const;
  void set_shadows(const bool shadow);
  virtual bool in_shadow(const Ray& ray, ShadeRec& sr) const = 0;
  virtual double G(const ShadeRec& sr) const; /* for area lights */
  virtual double pdf(const ShadeRec& sr) const; /* for area lights */
protected:
  bool shadows;
};

#endif