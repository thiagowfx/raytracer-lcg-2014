#ifndef _AREALIGHT_MINE_
#define _AREALIGHT_MINE_

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

    /** Part of the geometric factor of the object. */
    virtual double G(const ShadeRec&) const;
    virtual double pdf(const ShadeRec&) const;
    
  private:
    /** Form of this area light. */
    GeometricObject* object_ptr = NULL;
    /** An emissive material. */
    Material* material_ptr = NULL;
    /** Sample point on the surface. */
    Vector3d sample_point;
    /** Normal at sample point. */
    Vector3d light_normal;
    /** Unit vector from hit point (being shaded) to sample point. (on
	light surface) */
    Vector3d wi;
  };

  
  inline void AreaLight::set_object(GeometricObject* o) {
    this->object_ptr = o;
    this->material_ptr = this->object_ptr->get_material();
  }
}

#endif // _AREALIGHT_MINE_
