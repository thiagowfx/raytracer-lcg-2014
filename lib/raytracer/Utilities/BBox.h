#ifndef _BBOX_MINE_
#define _BBOX_MINE_

#include "Utilities.h"
#include "Ray.h"

/**
 * @brief Bounding box.
 */
class BBox {
 public:
  BBox();
  BBox(const double x0, const double x1,
       const double y0, const double y1,
       const double z0, const double z1);
  BBox(const Vector3d p0, const Vector3d p1);
  BBox(const BBox&);
  ~BBox();
  bool hit(const Ray&) const;
  bool inside(const Vector3d&) const;
 private:
  double x0, x1, y0, y1, z0, z1;
};

#endif // _BBOX_MINE_
