#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "ShadeRec.h"
#include "World.h"

/** @brief Point Light.
 *
 *  Represents a point light, having a position, a color and an intensity.
 */
class PointLight: public Light {
 public:
  PointLight();
  PointLight(const PointLight& a);
  virtual Light* clone() const;
  PointLight& operator= (const PointLight& rhs);
  virtual ~PointLight();
  virtual Vector3d get_direction(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);
  void set_location(Vector3d);
  void set_location(double,double,double);
  void scale_radiance(double);
  virtual bool in_shadow(const Ray& ray, ShadeRec& sr) const;

 private:
  double ls = 1.0; /**< Radiance of light. */
  RGBColor color = white; /**< Color of light. */
  Vector3d location = Vector3d::Zero(); /**< Location of light. */
};


inline void PointLight::set_location(Vector3d location) {
  this->location = location;
}


inline void PointLight::set_location(double x, double y, double z) {
  this->location = Vector3d(x,y,z);
}


inline void PointLight::scale_radiance(double ls) {
  this->ls = ls;
}

#endif
