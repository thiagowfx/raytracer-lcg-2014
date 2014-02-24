#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Constants.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Material.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class GeometricObject {	
	
 public:	
  GeometricObject();		
  GeometricObject(const GeometricObject& object); 
  virtual GeometricObject* clone() const = 0;
  virtual ~GeometricObject ();	
  virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
  Material* get_material() const;
  virtual void set_material(Material* mPtr);
  void set_color(RGBColor& color);
  RGBColor get_color() const;
	
 protected:
  /* mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const */
  mutable Material* material_ptr;
  RGBColor color;
  GeometricObject& operator= (const GeometricObject& rhs);
};


inline Material* GeometricObject::get_material() const {
  return material_ptr;
}

inline void GeometricObject::set_color(RGBColor &color) {
  this->color = color;
}

inline RGBColor GeometricObject::get_color() const {
  return color;
}


#endif
