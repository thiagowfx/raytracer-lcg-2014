#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient: public Light {
  
 public:
  Ambient(); 
  Ambient(const Ambient& a);
  virtual ~Ambient();
  virtual Light* clone() const;	
  Ambient& operator= (const Ambient& rhs); 
  void scale_radiance(const float b);
  void set_color(const RGBColor& c);
  virtual Vector3d get_direction(ShadeRec& s); 
  virtual RGBColor L(ShadeRec& s);
	
 private:
  float	   ls;
  RGBColor color;
  
};


inline void Ambient::scale_radiance(const float b) { 
  ls = b;
}

inline void Ambient::set_color(const RGBColor& c) {
  color = c;
}

#endif
