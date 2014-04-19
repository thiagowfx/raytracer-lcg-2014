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
  void scale_radiance(const double b);
  void set_color(const RGBColor&);
  void set_color(double,double,double);
  virtual Vector3d get_direction(ShadeRec& s); 
  virtual RGBColor L(ShadeRec& s);
  virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
 private:
  double radiance;
  RGBColor color;               // light color  
};


inline void Ambient::scale_radiance(const double b) {
  radiance = b;
}

inline void Ambient::set_color(const RGBColor& color) {
  this->color = color;
}

inline void Ambient::set_color(double r, double g, double b) {
  color.r = r;
  color.g = g;
  color.b = b;
}

#endif
