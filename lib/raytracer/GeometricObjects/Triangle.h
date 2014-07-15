#ifndef _TRIANGLE_MINE_
#define _TRIANGLE_MINE_

#include "GeometricObject.h"

namespace Raytracer {
  /**
   * @brief A triangle is defined by its three vertexes.
   */
  class Triangle: public GeometricObject {
  public:
    /** Construct a triangle with the given vertexes. */
    Triangle(const Vector3d&, const Vector3d&, const Vector3d&);
    Triangle(const Triangle&);
    ~Triangle();
    virtual Triangle* clone() const;
    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  private:
    /** Compute the normal to the triangle, its direction is defined by counter-clockwise order of the vertexes (right hand rule). */
    void compute_normal();   
    /* Triangle vertexes. */
    Vector3d v0, v1, v2;
    /** Normal. */
    Vector3d normal;
    /** Bounding box. */
    BBox *bbox_ptr;
  };
}

#endif // _TRIANGLE_MINE_
