#ifndef _DISK_MINE_
#define _DISK_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A disk is a filled circle, defined by its center and a radius, plus a normal (which defines a plane). It is like a 2D Sphere.
   */
  class Disk : public GeometricObject {
  public:
    /** Construct a disk, with a center, radius and normal (which defines a plane). */
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
