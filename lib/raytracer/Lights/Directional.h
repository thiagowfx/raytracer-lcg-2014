#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "World.h"          // needed later on for shadows
#include "ShadeRec.h"

class Directional: public Light {

 public:
  Directional();
  Directional(const Directional& dl);
  virtual Light* clone() const;
  Directional& operator= (const Directional& rhs);
  virtual ~Directional();
  void scale_radiance(const double b);
  void set_color(const RGBColor&);
  void set_color(double,double,double);
  void set_direction(Vector3d);
  void set_direction(double,double,double);
  virtual Vector3d get_direction(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);
  virtual bool in_shadow(const Ray& ray, ShadeRec& sr) const;

 private:
  double ls; /**< Radiance of light. */
  RGBColor color; /**< Color of light. */
  Vector3d direction; /**< Direction of light. */
};


inline void Directional::scale_radiance(const double b) {
  ls = b;
}


inline void Directional::set_color(const RGBColor& color) {
  this->color = color;
}

inline void Directional::set_color(double r, double g, double b) {
  color.r = r;
  color.g = g;
  color.b = b;
}


inline void Directional::set_direction(Vector3d d) {
  dir = d;
  dir.normalize();
}


inline void Directional::set_direction(double x, double y, double z) {
  dir(0) = x;
  dir(1) = y;
  dir(2) = z;
  dir.normalize();
}

#endif
