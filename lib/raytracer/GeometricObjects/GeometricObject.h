#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "BBox.h"
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
    GeometricObject(const GeometricObject&);
    virtual ~GeometricObject();
    virtual GeometricObject* clone() const = 0;

    /* Getters. */
    Material* get_material() const;
    RGBColor get_color() const;
    bool casts_shadows() const;
    // virtual BBox get_bounding_box() const;

    /* Setters. */
    virtual void set_material(Material*);
    void set_color(const RGBColor&);
    void set_shadows(const bool);

    /** Return true if the given ray hit the object. In this case and if the ray is primary,
     * shading information  is stored in tmin and in the ShadeRec object. */
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const = 0;

    /* The following three functions are needed for objects which are area lights. */
    /** Return a sample point on the object for area light shading. */
    virtual Vector3d sample();
    virtual double pdf(const ShadeRec&);
    virtual Vector3d get_normal(const Vector3d&);

  protected:
    /* mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const */
    mutable Material* material_ptr = NULL;

    /** Color for MultipleObjects tracer. */
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
