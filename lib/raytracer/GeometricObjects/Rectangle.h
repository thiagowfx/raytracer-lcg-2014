#ifndef _RECTANGLE_MINE_
#define _RECTANGLE_MINE_

#include "Sampler.h"
#include "GeometricObject.h"

namespace Raytracer {
  class Rectangle: public GeometricObject {
  public:
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b);
    Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b, const Vector3d& n);
    virtual Rectangle* clone() const;
    Rectangle(const Rectangle&);
    ~Rectangle();
    // BBox get_bounding_box();
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;

    /* the following functions are used when the rectangle is a light source */
    virtual void set_sampler(Sampler* sampler);
    virtual Vector3d sample();
    virtual double pdf(ShadeRec& sr);
    virtual Vector3d get_normal(const Vector3d& p);

  private:
    Vector3d p0;                // corner vertex
    Vector3d a, b; /** sides */
    double a_len_squared, b_len_squared; /** square of length of sides */
    Vector3d normal;
    double area;             // for rectangular lights
    double inv_area;         // for rectangular lights
    Sampler* sampler_ptr;    // for rectangular lights
  };
}

#endif // _RECTANGLE_MINE_
