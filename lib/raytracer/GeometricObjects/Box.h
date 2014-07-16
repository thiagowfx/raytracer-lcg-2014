#ifndef _BOX_MINE_
#define _BOX_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief An axis-aligned box, defined by two opposite vertexes in the same plane.
   */
  class Box: public GeometricObject {
  public:
    /** Construct an axis-aligned box, given the coordinates of its opposite vertexes. */
    Box(const double x0, const double x1,
        const double y0, const double y1,
        const double z0, const double z1);
    /** Construct an axis-aligned box from two opposite vertexes in the same plane. */
    Box(const Vector3d p0, const Vector3d p1);
    Box(const Box&);
    virtual ~Box();
    virtual Box* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Get the normal to a given face. */
    virtual Vector3d get_normal(const int) const;
    /** Vertex coordinates. */
    double x0, y0, z0;
    /** Opposite Vertex coordinates. */
    double x1, y1, z1;
  };
}

#endif // _BOX_MINE_
