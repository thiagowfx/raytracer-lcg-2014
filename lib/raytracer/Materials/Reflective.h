#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "PerfectSpecular.h"

namespace Raytracer {
  class Reflective: public Phong {

  public:
    Reflective();
    Reflective(const Reflective&);
    virtual Reflective* clone() const;
    ~Reflective();
    void set_kr(const double);
    void set_cr(const RGBColor&);
    virtual RGBColor shade(ShadeRec&);
    /** Direct illumination + reflective illumination + reflections. */
    static Reflective* generic(RGBColor);
    /** Black-ish, just reflections. */
    static Reflective* generic_uncolored();
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
