#ifndef _SHADEREC_MINE_
#define _SHADEREC_MINE_

#include "Ray.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  class Material;
  class World;

  /**
   * @brief Helper object to store information for shading.
   * There is no default constructor as the World reference always has to be initialized.
   * There is also no assignment operator as we don't want to assign the world.
   */
  class ShadeRec {
  public:
    /** Constructor. */
    ShadeRec(World& wr);

    /** Copy constructor. */
    ShadeRec(const ShadeRec& sr);

    /** Destructor. */
    ~ShadeRec();

    /** Did the ray hit any object? */
    bool hit_an_object = false;

    /** Pointer to the nearest hit object material. */
    Material* material_ptr = NULL;

    /** World coordinates of intersection. */
    Vector3d hit_point = Vector3d::Zero(); // world coordinates of intersection

    /** World coordinates of hit point on generic object (used for texture transformations). */
    Vector3d local_hit_point = Vector3d::Zero();

    /** Normal at hit point. */
    Vector3d normal = Vector3d::Zero();

    /** Used for specular highlights and area lights. */
    Ray ray;

    /** Recursion depth, for reflected rays. */
    int depth = 0;

    /** Ray parameter. */
    double t = 0.0;

    /** World reference. */
    World& w;
  };
}

#endif // _SHADEREC_MINE_
