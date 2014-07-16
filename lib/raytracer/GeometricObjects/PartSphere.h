#ifndef _PARTSPHERE_MINE_
#define _PARTSPHERE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A part sphere is like a sphere, but defined within angle ranges. It is centered at the origin.
   */
  class PartSphere: public GeometricObject {
  public:
    /** Construct a part sphere centered at the origin with the given radius, plus angle ranges. */
    PartSphere(const double radius, const double min_polar_angle = 0.0, double max_polar_angle = M_PI, double min_azimuth_angle = 0.0, double max_azimuth_angle = 2 * M_PI);
    PartSphere(const PartSphere&);
    ~PartSphere();
    virtual PartSphere* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Get azimuth angle from the given point in sphere. */
    double get_azimuth_angle(const Vector3d& p) const;
    /** Radius. */
    double radius;
    /** Minimum polar angle. */
    double min_polar_angle;
    /** Maximum polar angle. */
    double max_polar_angle;
    /** Minimum azimuth angle. */
    double min_azimuth_angle;
    /** Maximum azimuth angle. */
    double max_azimuth_angle;
  };
}

#endif // _PARTSPHERE_MINE_
