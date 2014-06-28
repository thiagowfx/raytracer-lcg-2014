#ifndef __RAY__
#define __RAY__

#include <Eigen/Dense>
using Eigen::Vector3d;

class Ray {

 public:
  Vector3d o = Vector3d::Zero();	// origin (point)
  Vector3d d = Vector3d(0.0, 0.0, 1.0); // direction (vector)
  Ray();
  ~Ray();
  Ray(const Vector3d& origin, const Vector3d& dir);
  Ray(const Ray& ray);
  Ray& operator= (const Ray& rhs);
};

#endif
