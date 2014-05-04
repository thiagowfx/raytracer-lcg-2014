#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Utilities.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Material.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class GeometricObject {	
	
 public:	
  GeometricObject();		
  GeometricObject(const GeometricObject& object); 
  virtual ~GeometricObject ();	
  virtual GeometricObject* clone() const = 0;
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
  Material* get_material() const;
  virtual void set_material(Material* mPtr);
  void set_color(const RGBColor& color);
  RGBColor get_color() const;
  virtual bool shadow_hit(const Ray& ray, double& tmin) const = 0;
  /* returns a sample point on the object for area light shading */
  virtual Vector3d sample();
  bool casts_shadows() const;
  void set_shadows(const bool shadow);
	
 protected:
  /* mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const */
  mutable Material* material_ptr;
  RGBColor color;
  bool shadows;
  GeometricObject& operator= (const GeometricObject& rhs);
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

#endif
