#ifndef _BBOX_MINE_
#define _BBOX_MINE_

#include "Utilities.h"
#include "Ray.h"

namespace Raytracer {
  /**
   * @brief A bounding box encloses a geometric object to speed up
   * rendering times of complex geometric objects, but it is not a
   * geometric object itself, since it does not have a hit function
   * complaint to it.
   */
  class BBox {
  public:
    /** Construct a bounding box, given the coordinates of its opposite vertexes. */
    BBox(const double x0, const double x1,
         const double y0, const double y1,
         const double z0, const double z1);
    /** Construct a bounding box with the given opposite vertexes in the same plane. */
    BBox(const Vector3d p0, const Vector3d p1);
    BBox(const BBox&);
    virtual BBox* clone() const;
    ~BBox();
    /** Return true if the ray hits the box. */
    bool hit(const Ray&) const;
    /** Return true if the given point is inside the box. */
    bool inside(const Vector3d&) const;
    /** Vertex coordinates. */
    double x0, y0, z0;
    /** Opposite vertex coordinates. */
    double x1, y1, z1;
  };
}

#endif // _BBOX_MINE_
