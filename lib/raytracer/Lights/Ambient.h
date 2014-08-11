#ifndef _AMBIENT_MINE_
#define _AMBIENT_MINE_

#include "Light.h"

namespace Raytracer {
  /**
   * @brief A light that is present everywhere, adding a constant
   * ammount illumination for every object.
   */
  class Ambient: public Light {
  public:
    Ambient(const Ambient&);
    Ambient();
    virtual ~Ambient();
    virtual Light* clone() const;
    virtual bool operator==(const Ambient&) const;

    /** Return the name of this class. */
    virtual const char* to_string() const;
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    virtual bool in_shadow(const Ray&, ShadeRec&) const;

    /* Setters. */
    void set_radiance(const double);
    void set_color(const RGBColor);

    /* Getters. */
    double get_radiance() const;
    RGBColor get_color() const;

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Light);
      ar & BOOST_SERIALIZATION_NVP(ls);
      ar & BOOST_SERIALIZATION_NVP(color);
    }

  protected:
    /** Radiance of light. */
    double ls = 1.0;
    /** Color of light. */
    RGBColor color = white;
  };


  inline void Ambient::set_radiance(const double ls) {
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
