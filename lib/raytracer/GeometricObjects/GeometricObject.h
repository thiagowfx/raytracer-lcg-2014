#ifndef _GEOMETRICOBJECT_MINE_
#define _GEOMETRICOBJECT_MINE_

#include "BBox.h"
#include "Material.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Utilities.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief A geometric object, which must have a hit function, usually
   * defined from an implicit equation.
   */
  class GeometricObject {
  public:
    GeometricObject();
    GeometricObject(const GeometricObject&);
    virtual ~GeometricObject();
    virtual GeometricObject* clone() const = 0;

    /* Getters. */
    /** Get object material. */
    Material* get_material() const;
    /** Does this object cast shadows? */
    bool get_shadows() const;

    /* Setters. */
    virtual void set_material(Material*);
    virtual void set_shadows(const bool);

    /** Return true if the given ray hit the object. In this case and
     * if the ray is primary, shading information is stored in tmin
     * and in the ShadeRec object. */
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const = 0;

    /** Return a sample point on the object for area light shading. */
    virtual Vector3d sample();
    /** For area light shading. */
    virtual double pdf(const ShadeRec&);
    /** Return the normal of a sample point on the object, required for
	area light shading. Works for planar objects and for objects
	that are defined by a single implicit function. */
    virtual Vector3d get_normal(const Vector3d&);

  protected:
    /* mutable allows Compound::hit, Instance::hit and Grid::hit to
       assign to material_ptr; hit functions are const */
    mutable Material* material_ptr = NULL;

    /** Does this object cast shadows? */
    bool shadows = true;
  };


  inline Material* GeometricObject::get_material() const {
    return material_ptr;
  }
}

#endif // _GEOMETRICOBJECT_MINE_
