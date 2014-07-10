#ifndef _ANNULUS_MINE
#define _ANNULUS_MINE

#include "GeometricObject.h"

namespace Raytracer {
  class Annulus : public GeometricObject {
  public:
    Annulus(const Vector3d& center, double inner_radius, double outer_radius, const Vector3d& normal);
    Annulus(const Annulus&);
    ~Annulus();
    virtual Annulus* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Center point. */
    Vector3d center;

    /** Inner dadius. */
    double inner_radius;

    /** Outer radius. */
    double outer_radius;

    /** Normal. */
    Vector3d normal;
  };
}

#endif // _ANNULUS_MINE
