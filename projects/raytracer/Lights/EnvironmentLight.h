#ifndef __ENVIRONMENT_LIGHT__
#define __ENVIRONMENT_LIGHT__

#include "Light.h"
#include "Sampler.h"
#include "Material.h"

class EnvironmentLight: public Light {

 public:
  EnvironmentLight();
  EnvironmentLight(const EnvironmentLight& al);
  virtual Light* clone() const;
  virtual ~EnvironmentLight();
  EnvironmentLight& operator= (const EnvironmentLight& rhs);
  void set_sampler(Sampler* sampler);
  void set_material(Material* material);
  virtual Vector3d get_direction(ShadeRec& s);
  virtual RGBColor L(ShadeRec& sr);
  virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
  virtual double pdf(const ShadeRec& sr) const;

 private:
  Sampler* sampler_ptr;
  Material* material_ptr;
  Vector3d u, v, w;
  Vector3d wi;
};

#endif
