#ifndef _RAY_MINE_
#define _RAY_MINE_

#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief A ray, which has an origin and a direction.
   */
  class Ray {
  public:
    Ray();
    /** Create a ray at the specified origin, in the specified direction. */
    Ray(const Vector3d& origin, const Vector3d& direction);
    Ray(const Ray& ray);
    ~Ray();
    /** Origin point. */
    Vector3d origin = Vector3d::Zero();
    /** Direction vector. */
    Vector3d direction = Vector3d(1.0, 0.0, 0.0);
  };

  /** Ray type.
   * Primary rays are shot by a camera, and
   * shadow rays are shot by objects to test intersection with lights. */
  enum Ray_t { PRIMARY_RAY, SHADOW_RAY };
}

#endif // _RAY_MINE_
