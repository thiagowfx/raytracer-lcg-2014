#ifndef _RECTANGLE_MINE_
#define _RECTANGLE_MINE_

#include "Sampler.h"
#include "GeometricObject.h"

namespace Raytracer {
  /** A rectangle is defined by a corner vertex and two vectors who origin from it. */
  class Rectangle: public GeometricObject {
  public:
    /** Construct a rectangle with corner vertex p0, and vectors a and b. Normal is automatically built. */
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b);
    /** Construct a rectangle with corner vertex p0, vectors a and b, and the given normal. */
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b, const Vector3d& n);
    virtual Rectangle* clone() const;
    Rectangle(const Rectangle&);
    ~Rectangle();
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

    /* the following functions are used when the rectangle is a light source */
    virtual void set_sampler(Sampler* sampler);
    virtual Vector3d sample();
    virtual double pdf(ShadeRec& sr);
    virtual Vector3d get_normal(const Vector3d& p);
  private:
    /** A corner vertex. */
    Vector3d p0;
    /* Vectors with p0 as their origin. */
    Vector3d a, b;
    /* Normal. */
    Vector3d normal;
    double area;             // for rectangular lights
    Sampler* sampler_ptr;    // for rectangular lights
  };
}

#endif // _RECTANGLE_MINE_
