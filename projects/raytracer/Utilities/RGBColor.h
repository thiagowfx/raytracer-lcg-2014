#ifndef __RGB_COLOR__
#define __RGB_COLOR__

#include <algorithm>
#include "Randomness.h"
using namespace std;

class RGBColor {
public:
  double r, g, b;

public:
  RGBColor();
  RGBColor(double, double, double);
  RGBColor(const RGBColor& c);
  ~RGBColor();
  RGBColor& operator= (const RGBColor& rhs);
  RGBColor operator+ (const RGBColor& c) const;
  RGBColor& operator+= (const RGBColor& c);
  RGBColor operator* (const double a) const;
  RGBColor& operator*= (const double a);
  RGBColor operator/ (const double a) const;
  RGBColor& operator/= (const double a);
  RGBColor operator* (const RGBColor& c) const;
  bool operator== (const RGBColor& c) const;
  bool operator!= (const RGBColor& c) const;
  RGBColor powc(double p) const;
  double average() const;
  RGBColor max_to_one() const;
  RGBColor clamp_to_red() const; /* Set color to red if any component is greater than one */
};


inline RGBColor RGBColor::operator+ (const RGBColor& c) const {
  return RGBColor(r + c.r, g + c.g, b + c.b);
}


inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
  r += c.r;
  g += c.g;
  b += c.b;

  return *this;
}


inline RGBColor RGBColor::operator* (const double a) const {
  return RGBColor (r * a, g * a, b * a);
}


inline RGBColor& RGBColor::operator*= (const double a) {
  r *= a;
  g *= a;
  b *= a;

  return *this;
}


inline RGBColor RGBColor::operator/ (const double a) const {
  return RGBColor (r / a, g / a, b / a);
}


inline RGBColor& RGBColor::operator/= (const double a) {
  r /= a;
  g /= a;
  b /= a;

  return *this;
}


inline RGBColor RGBColor::operator* (const RGBColor& c) const {
  return RGBColor (r * c.r, g * c.g, b * c.b);
}


inline bool RGBColor::operator== (const RGBColor& c) const {
  return compareDouble(r, c.r) && compareDouble(g, c.g) && compareDouble(b, c.b);
}


inline bool RGBColor::operator!= (const RGBColor& c) const {
  return ! operator==(c);
}


inline double RGBColor::average() const {
  return (r + g + b)/3.0;
}


/* Multiplication by a double on the left */
RGBColor operator* (const double a, const RGBColor& c);

inline RGBColor operator* (const double a, const RGBColor& c) {
  return RGBColor (a * c.r, a * c.g, a * c.b);
}

#endif
