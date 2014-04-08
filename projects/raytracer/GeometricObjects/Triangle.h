#ifndef __TRIANGLE__
#define __TRIANGLE__


#include "GeometricObject.h"

class Triangle: public GeometricObject {

 public:
  Triangle();
  Triangle(const Vector3d& a, const Vector3d& b, const Vector3d& c);
  virtual Triangle* clone() const;
  Triangle(const Triangle& triangle);
  ~Triangle();
  Triangle& operator= (const Triangle& rhs);
  /* virtual BBox get_bounding_box(); */
  void compute_normal();
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
  /* virtual bool shadow_hit(const Ray& ray, double& tmin) const; */

 private:
  Vector3d   v0, v1, v2;
  Vector3d    normal;
  
};

#endif
