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
  /* virtual bool casts_shadows() const; */
  /* virtual void set_shadows(bool _s); */
  void set_location(Vector3d l);
  void scale_radiance(float _r);
  /* bool in_shadow(const Ray& ray, const ShadeRec& sr) const; */
  virtual float G(const ShadeRec& sr) const;
  virtual float pdf(const ShadeRec& sr) const;
  
 private:
  float    ls;                  // radiant scale factor
  RGBColor color;
  Vector3d location;
};


/* inline bool PointLight::casts_shadows() const { */
/*   return Light::casts_shadows(); */
/* } */


/* inline void PointLight::set_shadows(bool _s) { */
/*   return Light::set_shadows(_s); */
/* } */


inline void PointLight::set_location(Vector3d l) {
  this->location = l;
}


inline void PointLight::scale_radiance(float _r) {
  ls *= _r;
}

#endif
