#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Constants.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include <Eigen/Dense>

using Eigen::Vector3d;					

class GeometricObject {	
	
 public:	
  GeometricObject(void);		
  GeometricObject(const GeometricObject& object); 
  virtual GeometricObject* clone(void) const = 0;
  virtual ~GeometricObject (void);	
  virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

  // the following three functions are only required for Chapter 3
  void set_color(const RGBColor& c);
  void set_color(const float r, const float g, const float b);
  RGBColor get_color(void);
	
 protected:
  RGBColor color; // only used for Bare Bones ray tracing
  GeometricObject& operator= (const GeometricObject& rhs);
};


inline void GeometricObject::set_color(const RGBColor& c) {
  color = c;
}

inline void GeometricObject::set_color(const float r, const float g, const float b) {
  color.r = r;
  color.b = b;
  color.g = g;
}

inline RGBColor GeometricObject::get_color(void) {
  return (color);
}

#endif
