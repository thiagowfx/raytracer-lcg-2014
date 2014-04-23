#ifndef __LIGHT__
#define __LIGHT__

#include "Constants.h"
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
  virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;
 protected:
  bool shadows;
};


#endif
