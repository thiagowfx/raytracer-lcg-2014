#ifndef _RAY_MINE_
#define _RAY_MINE_

#include "BoostMine.hpp"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief A ray, which has an origin and a direction.
   */
  class Ray {
  public:
    /** Create a ray at the specified origin, with the specified direction. */
    Ray(const Vector3d& origin, const Vector3d& direction);
    Ray();
    Ray(const Ray&);
    ~Ray();
    bool operator==(const Ray&) const;
    friend std::ostream& operator<<(std::ostream&, const Ray&);

    /** Origin point. */
    Vector3d origin;
    
    /** Direction vector. */
    Vector3d direction;

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(origin);
      ar & BOOST_SERIALIZATION_NVP(direction);
    }
  };

  /** Ray type.  Primary rays are shot by a camera, and shadow rays are
   * shot by objects to test intersection with lights. */
  enum Ray_t { PRIMARY_RAY, SHADOW_RAY };
}

#endif // _RAY_MINE_
