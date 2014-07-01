#ifndef __RAY__
#define __RAY__

#include <Eigen/Dense>
using Eigen::Vector3d;

/** @brief A ray, which has an origin and a direction.
 */
class Ray {
 public:
  Ray();
  ~Ray();
  Ray(const Vector3d& origin, const Vector3d& dir);
  Vector3d o = Vector3d::Zero(); /**< Origin point. */
  Vector3d d = Vector3d(0.0, 0.0, 1.0); /**< Direction vector. */
  Ray(const Ray& ray);
  Ray& operator= (const Ray& rhs);
};

#endif
