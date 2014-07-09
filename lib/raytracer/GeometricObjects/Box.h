#ifndef _BOX_MINE_
#define _BOX_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Box: public GeometricObject {
  public:
    Box(const double x0, const double x1,
        const double y0, const double y1,
        const double z0, const double z1);
    Box(const Vector3d p0, const Vector3d p1);
    Box(const Box&);
    virtual ~Box();
    virtual Box* clone() const;
    
    virtual BBox get_bounding_box() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
    virtual Vector3d get_normal(const int face_hit) const;
  private:
    double x0, y0, z0;
    double x1, y1, z1;
  };
}

#endif // _BOX_MINE_
