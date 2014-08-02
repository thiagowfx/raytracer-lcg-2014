#ifndef _ENVIRONMENTLIGHT_MINE_
#define _ENVIRONMENTLIGHT_MINE_

#include "Light.h"
#include "MultiJittered.h"
#include "ShadeRec.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief An EnvironmentLight is like an infinite sphere which emits
   * light.
   */
  class EnvironmentLight: public Light {
  public:
    EnvironmentLight();
    EnvironmentLight(const EnvironmentLight&);
    virtual Light* clone() const;
    virtual ~EnvironmentLight();

    /* Setters. */
    void set_sampler(Sampler*);
    void set_material(Material*);
    
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;
    virtual double pdf(const ShadeRec&) const;
  private:
    Sampler* sampler_ptr = NULL;
    /** This wil be an emissive material. */
    Material* material_ptr = NULL;
    Vector3d u = Vector3d::Zero();
    Vector3d v = Vector3d::Zero();
    Vector3d w = Vector3d::Zero();
    /** Unit direction from hit point being shaded to sample point on light. */
    Vector3d wi = Vector3d::Zero();
  };


  inline void EnvironmentLight::set_material(Material* material_ptr) {
    this->material_ptr = material_ptr;
  }
}


#endif // _ENVIRONMENTLIGHT_MINE_
