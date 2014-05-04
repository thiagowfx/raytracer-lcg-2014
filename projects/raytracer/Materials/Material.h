#ifndef __MATERIAL__
#define __MATERIAL__

// #include "World.h" // required for the shade function in all derived classes
#include "Utilities.h"
#include "RGBColor.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class Material {
  
 public:	
  Material();
  virtual ~Material();
  Material(const Material& material);
  virtual Material* clone() const = 0; 
  virtual RGBColor shade(ShadeRec& sr) = 0;
  virtual RGBColor whitted_shade(ShadeRec& src);
  virtual RGBColor area_light_shade(ShadeRec& sr);
  virtual RGBColor path_shade(ShadeRec& sr);
  virtual RGBColor get_color() const = 0;
		
 protected:
  Material& operator= (const Material& rhs);  
};

#endif
