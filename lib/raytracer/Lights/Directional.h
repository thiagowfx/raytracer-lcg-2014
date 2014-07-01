#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

/** @brief Directional Light.
 *
 *  Represents a directional light, having a direction, a color and an intensity.
 */
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
  double ls = 1.0; /**< Radiance of light. */
  RGBColor color = white; /**< Color of light. */
  Vector3d direction = Vector3d(0.0, 1.0, 0.0); /**< Direction of light. */
};


inline void Directional::scale_radiance(const double ls) {
  this->ls = ls;
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
  direction = d;
  direction.normalize();
}


inline void Directional::set_direction(double x, double y, double z) {
  direction = Vector3d(x,y,z);
  direction.normalize();
}

#endif
