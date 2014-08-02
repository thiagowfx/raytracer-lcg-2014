#ifndef _PLANE_MINE_
#define _PLANE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A plane is defined by a point and a normal.
   */
  class Plane : public GeometricObject {
  public:
    /** Construct a plane which passes at the given point, with the given normal. */
    Plane(const Vector3d& point, const Vector3d& normal);
    Plane(const Plane&);
    ~Plane();
    virtual Plane* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;  
  private:
    /** A point in the plane. */
    Vector3d point;    
    /** Normal to the plane. */
    Vector3d normal;
  };
}

#endif // _PLANE_MINE_
