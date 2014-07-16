#ifndef _ANNULUS_MINE_
#define _ANNULUS_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief An annulus is like a disk, but with a small disk is taken off from its surface. Two radius are specified.
   */
  class Annulus : public GeometricObject {
  public:
    /** Construct an annulus with the given center point, inner and outer radius, and a normal (which defines a plane). */
    Annulus(const Vector3d& center, double inner_radius, double outer_radius, const Vector3d& normal);
    Annulus(const Annulus&);
    ~Annulus();
    virtual Annulus* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Center point. */
    Vector3d center;
    /** Inner dadius. Should be smaller than the outer radius. */
    double inner_radius;
    /** Outer radius. Should be greater than the inner radius. */
    double outer_radius;
    /** Normal. */
    Vector3d normal;
  };
}

#endif // _ANNULUS_MINE_
