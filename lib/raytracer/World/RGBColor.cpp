#include "RGBColor.h"
#include <math.h>

namespace Raytracer {
  RGBColor::RGBColor() {}


  RGBColor::RGBColor(double r, double g, double b) :
    r(r),
    g(g),
    b(b) {
    normalize();
  }


  RGBColor::RGBColor(const RGBColor& c) :
    r(c.r),
    g(c.g),
    b(c.b)
  {}


  RGBColor::~RGBColor() {}


  RGBColor& RGBColor::operator= (const RGBColor& rhs) {
    if (this != &rhs) {
      r = rhs.r;
      g = rhs.g;
      b = rhs.b;
    }
    return *this;
  }


  RGBColor RGBColor::powc(double p) const {
    return RGBColor(pow(r, p), pow(g, p), pow(b, p));
  }


  RGBColor RGBColor::normalize() const {
    double max_value = max(r, max(g, b));
    return (max_value > 1.0) ? (*this / max_value) : *this;
  }


  RGBColor RGBColor::clamp_to_red() const {
    if (r > 1.0 || g > 1.0 || b > 1.0) {
      return RGBColor(1.0, 0.0, 0.0);
    }
    else {
      return *this;
    }
  }
}
