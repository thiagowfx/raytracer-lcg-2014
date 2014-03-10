#ifndef __LIGHT__
#define __LIGHT__

#include "Constants.h"
#include "RGBColor.h"
#include "Ray.h"
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
  virtual Vector3d get_direction(ShadeRec& sr) = 0; 
  virtual RGBColor L(ShadeRec& sr); // radiance
  
};


#endif
