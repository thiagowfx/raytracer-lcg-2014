#ifndef _TORUS_MINE_
#define _TORUS_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Torus: public GeometricObject {
  public:
    Torus(const double a, const double b);
    Torus(const Torus&);
    ~Torus();
    virtual Torus* clone() const;
    /** Find the normal vector at the specified position. This works
	because the torus is defined by a single implicit equation. */
    Vector3d compute_normal(const Vector3d& point) const;
    virtual BBox get_bounding_box() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

  private:
    /** Swept radius. */
    double a;

    /** Tube radius. */
    double b;

    /** Bounding box. */
    BBox bbox;
  };
}

#endif // _TORUS_MINE_
