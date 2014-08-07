#ifndef _PARTOPENCYLINDER_MINE_
#define _PARTOPENCYLINDER_MINE_

#include "OpenCylinder.h"

namespace Raytracer {
  /**
   * @brief A part open cylinder is like an open cylinder, however it
   * is only defined within an angle range.
   */
  class PartOpenCylinder: public OpenCylinder {
  public:
    /** Y coordinate from bottom and from top, radius, and angle range (minimum then maximum). */
    PartOpenCylinder(const double ybottom, const double ytop, const double radius, double min_azimuth_angle = 0.0, double max_azimuth_angle = 2 * M_PI);
    PartOpenCylinder(const PartOpenCylinder&);
    virtual ~PartOpenCylinder();
    virtual PartOpenCylinder* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Get azimuth angle from the given point in cylinder. */
    double get_azimuth_angle(const Vector3d& p) const;
    /** Minimum angle. */
    double min_azimuth_angle;
    /** Maximum angle. */
    double max_azimuth_angle;
  };
}

#endif // _PARTOPENCYLINDER_MINE_
