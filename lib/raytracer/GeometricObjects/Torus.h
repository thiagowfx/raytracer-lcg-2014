#ifndef _TORUS_MINE_
#define _TORUS_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A doughnut-shaped object, built around the y-axis, at the origin. It is defined by a swept radius and a tube radius.
   */
  class Torus: public GeometricObject {
  public:
    /** Construct a torus, where a is the swept radius and b is the tube radius. */
    Torus(const double a, const double b);
    Torus(const Torus&);
    ~Torus();
    virtual Torus* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Find the normal vector at the specified position. This works
        because the torus is defined by a single implicit equation. */
    Vector3d compute_normal(const Vector3d& point) const;
    /** Swept radius (size) */
    double a;
    /** Tube radius (thickness) */
    double b;
    /** Bounding box. */
    BBox *bbox_ptr;
  };
}

#endif // _TORUS_MINE_
