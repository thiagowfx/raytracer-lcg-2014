#ifndef _RGBCOLOR_MINE_
#define _RGBCOLOR_MINE_

#include "BoostMine.hpp"
#include <algorithm>

namespace Raytracer {
  /**
   * @brief Represents a color in the RGB format, components from 0.0 to 1.0.
   */
  class RGBColor {
  public:
    /** Create a RGBColor with the specified red, green and blue components. */
    RGBColor(float r, float g, float b);
    RGBColor(const RGBColor&);
    RGBColor();
    ~RGBColor();
    RGBColor& operator=(const RGBColor&);
    bool operator==(const RGBColor&) const;
    bool operator!=(const RGBColor&) const;
    RGBColor operator+ (const RGBColor&) const;
    RGBColor& operator+= (const RGBColor&);
    RGBColor operator* (const float) const;
    RGBColor& operator*= (const float);
    RGBColor operator/ (const float) const;
    RGBColor& operator/= (const float);
    RGBColor operator* (const RGBColor&) const;

    /** Red component, from 0.0 to 1.0. */
    float r = 0.0;

    /** Green component, from 0.0 to 1.0. */
    float g = 0.0;

    /** Blue component, from 0.0 to 1.0. */
    float b = 0.0;

    /** Color components are raised to the specified power. */
    RGBColor powc(float) const;

    /** Return the average of components. */
    float average() const;

    /** If any component is greater than one, then all components are divided by the maximum one. */
    RGBColor normalize() const;

    /** Return red if any component is greater than one. */
    RGBColor clamp_to_red() const;

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(r);
      ar & BOOST_SERIALIZATION_NVP(g);
      ar & BOOST_SERIALIZATION_NVP(b);
    }
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


  inline RGBColor RGBColor::operator* (const float a) const {
    return RGBColor (r * a, g * a, b * a);
  }


  inline RGBColor& RGBColor::operator*= (const float a) {
    r *= a;
    g *= a;
    b *= a;
    return *this;
  }


  inline RGBColor RGBColor::operator/ (const float a) const {
    return RGBColor (r / a, g / a, b / a);
  }


  inline RGBColor& RGBColor::operator/= (const float a) {
    r /= a;
    g /= a;
    b /= a;
    return *this;
  }


  inline RGBColor RGBColor::operator* (const RGBColor& c) const {
    return RGBColor (r * c.r, g * c.g, b * c.b);
  }


  inline bool RGBColor::operator==(const RGBColor& o) const {
    return
        r == o.r &&
        g == o.g &&
        b == o.b;
  }


  inline bool RGBColor::operator!= (const RGBColor& c) const {
    return !operator==(c);
  }


  inline float RGBColor::average() const {
    return (r + g + b)/3.0;
  }


  inline RGBColor operator* (const float a, const RGBColor& c) {
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
}

#endif // _RGBCOLOR_MINE_
