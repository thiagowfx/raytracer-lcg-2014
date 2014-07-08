#ifndef _AMBIENT_MINE_
#define _AMBIENT_MINE_

#include "Light.h"

namespace Raytracer {
  /**
   * @brief Light that is present everywhere.
   */
  class Ambient: public Light {
  public:
    Ambient();
    Ambient(const Ambient& a);
    virtual ~Ambient();
    virtual Light* clone() const;
    virtual Vector3d get_direction(ShadeRec& s);
    virtual RGBColor L(ShadeRec& s);
    void scale_radiance(const double b);
    void set_color(const RGBColor);
    double get_radiance() const;
    RGBColor get_color() const;
    virtual const char* to_string() const;
    
    /** Chapter 16: Always false. */
    virtual bool in_shadow(const Ray& ray, ShadeRec& sr) const;

  protected:
    /** Radiance of light. */
    double ls = 1.0;

    /** Color of light. */
    RGBColor color = white;
  };


  inline void Ambient::scale_radiance(const double ls) {
    this->ls = ls;
  }


  inline void Ambient::set_color(const RGBColor color) {
    this->color = color;
  }


  inline double Ambient::get_radiance() const {
    return ls;
  }


  inline RGBColor Ambient::get_color() const {
    return color;
  }
}

#endif // _AMBIENT_MINE_
