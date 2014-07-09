#ifndef _RAY_MINE_
#define _RAY_MINE_

#include <Eigen/Dense>
using Eigen::Vector3d;

/**
 * @brief A ray, which has an origin and a direction.
 */
class Ray {
 public:
  Ray();
  Ray(const Vector3d& origin, const Vector3d& direction);
  Ray(const Ray& ray);
  ~Ray();
  
  /** Origin point. */
  Vector3d origin = Vector3d::Zero();

  /** Direction vector. */
  Vector3d direction = Vector3d::Zero();
};

/** Ray type. */
enum Ray_t { PRIMARY_RAY, SHADOW_RAY };

#endif // _RAY_MINE_
