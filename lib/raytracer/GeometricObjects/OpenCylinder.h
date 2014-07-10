#ifndef _OPENCYLINDER_MINE
#define _OPENCYLINDER_MINE

#include "GeometricObject.h"

namespace Raytracer {

  /**
   * @brief An open cylinder is centered on the y axis and is defined by its extent in the y direction and its radius.
   */
  class OpenCylinder: public GeometricObject {
  public:
    OpenCylinder(const double ybottom, const double ytop, const double radius);
    OpenCylinder(const OpenCylinder&);
    virtual ~OpenCylinder();
    virtual OpenCylinder* clone () const;
    /** The code reverses the normal when the ray hits the inside surface, allows both
	sides to be shaded, but completely messes up transparency. */
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
    
  protected:
    /** Bottom y value. */
    double ybottom;

    /** Top y value. */
    double ytop;

    /** Radius. */
    double radius;
  };
}

#endif // _OPENCYLINDER_MINE
