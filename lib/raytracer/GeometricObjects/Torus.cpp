#include "Torus.h"


namespace Raytracer {
  Torus::Torus (const double a, const double b) :
    GeometricObject(),
    a(a),
    b(b),
    bbox(-a - b, a + b, -b, b, -a - b, a + b)
  {}


  Torus* Torus::clone() const {
    return new Torus(*this);
  }


  Torus::Torus (const Torus& torus) :
    GeometricObject(torus),
    a(torus.a),
    b(torus.b),
    bbox(torus.bbox)
  {}


  Torus::~Torus(){}


  Vector3d Torus::compute_normal(const Vector3d& p) const {
    Vector3d normal;
    double param_squared = a * a + b * b;
    double x = p(0);
    double y = p(1);
    double z = p(2);
    double sum_squared = x * x + y * y + z * z;
    normal(0) = 4.0 * x * (sum_squared - param_squared);
    normal(1) = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
    normal(2) = 4.0 * z * (sum_squared - param_squared);
    return normal.normalized();
  }


  BBox Torus::get_bounding_box() const {
    return bbox;
  }


  bool Torus::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    if (!bbox.hit(ray))
      return false;

    double x1 = ray.origin(0);
    double y1 = ray.origin(1);
    double z1 = ray.origin(2);
    double d1 = ray.direction(0);
    double d2 = ray.direction(1);
    double d3 = ray.direction(2);
    /** Coefficient array for the quartic equation. */
    double coeffs[5];
    /** Solution array for the quartic equation. */
    double roots[4];

    /* Define the coefficients of the quartic equation. */
    double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
    double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
    double f = x1 * d1 + y1 * d2 + z1 * d3;
    double four_a_sqrd = 4.0 * a * a;

    /* Constant term. */
    coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1);
    coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
    coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
    coeffs[3] = 4.0 * sum_d_sqrd * f;
    /* Coefficient of t^4. */
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;

    /* Find roots of the quartic equation. */
    int num_real_roots = SolveQuartic(coeffs, roots);
    bool  intersected = false;
    double t = kHugeValue;

    /* Ray misses the torus. */
    if (!num_real_roots)
      return false;

    /* Find the smallest root greater than kEpsilon, if any. The roots array is not sorted. */
    for (unsigned j = 0; j < num_real_roots; ++j)
      if (roots[j] > kEpsilon) {
        intersected = true;
        if (roots[j] < t) {
          t = roots[j];
        }
      }

    if(!intersected)
      return false;

    tmin = t;

    if (type == PRIMARY_RAY) {
      sr.local_hit_point = ray.origin + t * ray.direction;
      sr.normal = compute_normal(sr.local_hit_point);
    }
    return true;
  }
}
