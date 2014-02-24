#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "RGBColor.h"
#include "World.h"          // you will need this later on for shadows
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class Directional: public Light {
  
 public:
  Directional();   							
  Directional(const Directional& dl); 
  virtual Light* clone() const;			
  Directional& operator= (const Directional& rhs); 
  virtual ~Directional(); 				
  void scale_radiance(const float b);
  void set_color(const float c);
  void set_color(const RGBColor& c);
  void set_color(const float r, const float g, const float b); 		
  void set_direction(Vector3d d);
  void set_direction(float dx, float dy, float dz);
  virtual Vector3d get_direction(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);	
		
 private:
  float	   ls;			
  RGBColor color;
  Vector3d dir;                 // direction the light comes from
  
};


inline void Directional::scale_radiance(const float b) { 
  ls = b;
}


inline void Directional::set_color(const float c) {
  color.r = c;
  color.g = c;
  color.b = c;
}


inline void Directional::set_color(const RGBColor& c) {
  color = c;
}


inline void Directional::set_color(const float r, const float g, const float b) {
  color.r = r;
  color.g = g;
  color.b = b;
}


inline void Directional::set_direction(Vector3d d) {
  dir = d;
  dir.normalize();
}


inline void Directional::set_direction(float dx, float dy, float dz) {
  dir(0) = dx;
  dir(1) = dy;
  dir(2) = dz;  
  dir.normalize();
}


#endif
