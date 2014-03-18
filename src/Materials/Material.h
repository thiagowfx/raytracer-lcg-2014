#ifndef __MATERIAL__
#define __MATERIAL__

// #include "World.h" // required for the shade function in all derived classes
#include "RGBColor.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class Material {
  
 public:	
  Material();
  Material(const Material& material);
  virtual Material* clone() const = 0; 
  virtual ~Material();
  virtual RGBColor shade(ShadeRec& sr);	
		
 protected:
  Material& operator= (const Material& rhs);
  
};


#endif
