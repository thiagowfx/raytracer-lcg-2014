#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "RGBColor.h"
#include "World.h"          // needed later on for shadows
#include "ShadeRec.h"

class Directional: public Light {
  
 public:
  Directional();   							
  Directional(const Directional& dl); 
  virtual Light* clone() const;			
  Directional& operator= (const Directional& rhs); 
  virtual ~Directional(); 				
  void scale_radiance(const float b);
  void set_color(const RGBColor& c);
  void set_direction(Vector3d d);
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


inline void Directional::set_color(const RGBColor& color) {
  this->color = color;
}


inline void Directional::set_direction(Vector3d d) {
  dir = d;
  dir.normalize();
}

#endif
