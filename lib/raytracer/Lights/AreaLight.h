#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

namespace Raytracer {
  class AreaLight: public Light {
  public:
    AreaLight();
    AreaLight(const AreaLight&);
    virtual Light* clone() const;
    virtual ~AreaLight();
    void set_object(GeometricObject*);
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec& sr);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;
    virtual double G(const ShadeRec&) const;
    virtual double pdf(const ShadeRec&) const;
  private:
    GeometricObject* object_ptr = NULL;
    Material* material_ptr = NULL; // will be an emissive material
    Vector3d sample_point;
    Vector3d light_normal; // assigned in get_direction - which therefore can't be const for any light
    Vector3d wi; // unit direction from hit point being shaded to sample point on light surface
  };

  
  inline void AreaLight::set_object(GeometricObject* obj_ptr) {
    object_ptr = obj_ptr;
    material_ptr = object_ptr->get_material();
  }
}

#endif
