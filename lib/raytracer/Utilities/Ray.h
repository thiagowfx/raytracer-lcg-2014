#ifndef __RAY__
#define __RAY__

#include <Eigen/Dense>
using Eigen::Vector3d;

/**
 * @brief A ray, which has an origin and a direction.
 */
class Ray {
 public:
  /** Constrcutor. */
  Ray();

  /** Constructor. */
  Ray(const Vector3d& origin, const Vector3d& direction);

  /** Copy constructor. */
  Ray(const Ray& ray);
  
  /** Destructor. */
  ~Ray();
  
  /** Origin point. */
  Vector3d o = Vector3d::Zero();

  /** Direction vector. */
  Vector3d d = Vector3d(0.0, 0.0, 1.0);
};

/** Ray type. */
enum Ray_t { PRIMARY_RAY, SHADOW_RAY };

#endif
