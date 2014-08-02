#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "PerfectSpecular.h"

namespace Raytracer {
  class Reflective: public Phong {
  public:
    /**
     * @brief Construct a new Reflective material with the given color
     * (direct illumination + reflective illumination + reflections)
     */
    Reflective(const RGBColor&);
    Reflective(const Reflective&);
    virtual Reflective* clone() const;
    ~Reflective();

    virtual RGBColor shade(ShadeRec&);
    virtual RGBColor area_light_shade(ShadeRec&);

    /* Setters. */
    void set_kr(const double);
    void set_cr(const RGBColor&);
    /** Make this reflective material a pure mirror, black-ish, just
        with reflections. */
    void make_uncolored();

  private:
    PerfectSpecular* reflective_brdf = new PerfectSpecular();
  };


  inline void Reflective::set_kr(const double k) {
    reflective_brdf->set_kr(k);
  }


  inline void Reflective::set_cr(const RGBColor& c) {
    reflective_brdf->set_cr(c);
  }
}

#endif
