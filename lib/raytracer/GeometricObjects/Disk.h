#ifndef _DISK_MINE_
#define _DISK_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  class Disk : public GeometricObject {
  public:
    Disk(const Vector3d& center, double radius, const Vector3d& normal);
    Disk(const Disk&);
    ~Disk();
    virtual Disk* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Center point. */
    Vector3d center;

    /** Radius. */
    double radius;

    /** Normal. */
    Vector3d normal;
  };
}

#endif // _DISK_MINE_
