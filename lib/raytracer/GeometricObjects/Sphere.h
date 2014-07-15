#ifndef _SPHERE_MINE_
#define _SPHERE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A Sphere is defined by its center point and its radius.
   */
  class Sphere: public GeometricObject {
  public:
    /** Construct a sphere with the given center point and radius. */
    Sphere(const Vector3d& center, const double radius);
    Sphere(const Sphere&);
    ~Sphere();
    virtual Sphere* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Center point. */
    Vector3d center;
    /** Radius. */
    double radius;
  };
}

#endif // _SPHERE_MINE_
