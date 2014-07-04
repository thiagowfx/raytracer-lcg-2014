#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Material.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Utilities.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  class GeometricObject {
  public:
    GeometricObject();
    GeometricObject(const GeometricObject& object);
    virtual ~GeometricObject ();
    virtual GeometricObject* clone() const = 0;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
    Material* get_material() const;
    virtual void set_material(Material* mPtr);
    void set_color(const RGBColor& color);
    RGBColor get_color() const;
    /* returns a sample point on the object for area light shading */
    bool casts_shadows() const;
    void set_shadows(const bool shadow);
    /* the following three functions are needed for objects which are area lights */
    virtual Vector3d sample();
    virtual double pdf(const ShadeRec& sr);
    virtual Vector3d get_normal(const Vector3d& p);

  protected:
    /* mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const */
    mutable Material* material_ptr = NULL;
    RGBColor color = black;
    bool shadows = true;
  };


  inline Material* GeometricObject::get_material() const {
    return material_ptr;
  }

  inline void GeometricObject::set_color(const RGBColor& color) {
    this->color = color;
  }

  inline RGBColor GeometricObject::get_color() const {
    return color;
  }
}

#endif
