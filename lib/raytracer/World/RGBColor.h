#ifndef _RGBCOLOR_MINE_
#define _RGBCOLOR_MINE_

#include <algorithm>
#include <cmath>
using namespace std;

/**
 * @brief Represents a color in the RGB format, components from 0.0 to 1.0.
 */
class RGBColor {
 public:
  /** Create a black RGBColor. */
  RGBColor();
  /** Create a RGBColor with the specified red, green and blue components. */
  RGBColor(double r, double g, double b);
  RGBColor(const RGBColor&);
  RGBColor& operator=(const RGBColor&);
  ~RGBColor();

  /** Red component, from 0.0 to 1.0. */
  double r = 0.0;

  /** Green component, from 0.0 to 1.0. */
  double g = 0.0;

  /** Blue component, from 0.0 to 1.0. */
  double b = 0.0;

  /** C++ operators overloading. */
  RGBColor operator+ (const RGBColor&) const;
  RGBColor& operator+= (const RGBColor&);
  RGBColor operator* (const double) const;
  RGBColor& operator*= (const double);
  RGBColor operator/ (const double) const;
  RGBColor& operator/= (const double);
  RGBColor operator* (const RGBColor&) const;

  /** Return true if the colors are equal. */
  bool operator==(const RGBColor&) const;

  /** Return true if the colors are different. */
  bool operator!=(const RGBColor&) const;

  /** Color components are raised to the specified power. */
  RGBColor powc(double) const;

  /** Return the average of components. */
  double average() const;

  /** If any component is greater than one, then all components are divided by the maximum one. */
  RGBColor normalize() const;

  /** Return red if any component is greater than one. */
  RGBColor clamp_to_red() const;
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
  const double kEpsilon = 1.0e-7;
  return fabs(r - c.r) < kEpsilon && fabs(g - c.g) < kEpsilon && fabs(b - c.b) < kEpsilon;
}


inline bool RGBColor::operator!= (const RGBColor& c) const {
  return !operator==(c);
}


inline double RGBColor::average() const {
  return (r + g + b)/3.0;
}


inline RGBColor operator* (const double a, const RGBColor& c) {
  return RGBColor (a * c.r, a * c.g, a * c.b);
}

/* Color constants. */
const RGBColor black(0.0, 0.0, 0.0);
const RGBColor dark_grey(0.25, 0.25, 0.25);
const RGBColor dark_gray(dark_grey);
const RGBColor grey(0.50, 0.50, 0.50);
const RGBColor gray(grey);
const RGBColor light_grey(0.75, 0.75, 0.75);
const RGBColor light_gray(light_grey);
const RGBColor white(1.0, 1.0, 1.0);

const RGBColor brown(0.71, 0.40, 0.16);
const RGBColor red(1.0, 0.0, 0.0);

const RGBColor green(0.0, 1.0, 0.0);
const RGBColor light_green(0.65, 1.0, 0.30);
const RGBColor dark_green(0.0, 0.41, 0.41);

const RGBColor blue(0.0, 0.0, 1.0);
const RGBColor light_purple(0.65, 0.3, 1.0);
const RGBColor dark_purple(0.5, 0.0, 1);

const RGBColor yellow(1.0, 1.0, 0.0);
const RGBColor dark_yellow(0.61, 0.61, 0.0);
const RGBColor orange(1.0, 0.75, 0.0);

#endif // _RGBCOLOR_MINE_