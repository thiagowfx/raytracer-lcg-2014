#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "ShadeRec.h"
#include "World.h"

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
  virtual void scale_radiance(double);
  virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
  
 private:
  double radiance;
  RGBColor color;
  Vector3d location;
};


inline void PointLight::set_location(Vector3d v) {
  location = v;
}


inline void PointLight::set_location(double x, double y, double z) {
  location(0) = x;
  location(1) = y;
  location(2) = z;
}


inline void PointLight::scale_radiance(double r) {
  radiance *= r;
}

#endif
