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

    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;
    virtual Vector3d get_direction(ShadeRec&);
    
    /* Setters. */
    void set_object(GeometricObject*);

    virtual double G(const ShadeRec&) const;
    virtual double pdf(const ShadeRec&) const;
  private:
    GeometricObject* object_ptr = NULL;
    /** This will be an emissive material. */
    Material* material_ptr = NULL;
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
