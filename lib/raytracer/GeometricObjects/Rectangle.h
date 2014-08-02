#ifndef _RECTANGLE_MINE_
#define _RECTANGLE_MINE_

#include "Sampler.h"
#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A rectangle is defined by a corner vertex and two vectors who
   *   origin from it.
   */
  class Rectangle: public GeometricObject {
  public:
    /** Construct a rectangle with corner vertex p0, and vectors a and
        b. Normal is automatically built. */
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b);
    /** Construct a rectangle with corner vertex p0, vectors a and b,
        and the given normal. */
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b, const Vector3d& n);
    virtual Rectangle* clone() const;
    Rectangle(const Rectangle&);
    ~Rectangle();
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

    /* The following functions are used when the rectangle is a light
       source / has an emissive material, for area light shading. */
    virtual void set_sampler(Sampler*);
    /** Get a sample point on the rectangle. Warning! This only works
        for squares, actually. */
    virtual Vector3d sample();
    /** The pdf of a rectangle is its inverse area. */
    virtual double pdf(ShadeRec&);
    /** Return the normal of the rectangle; it is the same for every
        point. */
    virtual Vector3d get_normal(const Vector3d&);
  private:
    /** A corner vertex. */
    Vector3d p0;
    /* Vectors with p0 as their origin. */
    Vector3d a, b;
    /* Normal. */
    Vector3d normal;
    /** Inverse area of the rectangle; for area light shading. */
    double inv_area;
    /** Rectangle sampler; for area light shading. */
    Sampler* sampler_ptr = NULL;
  };
}

#endif // _RECTANGLE_MINE_
