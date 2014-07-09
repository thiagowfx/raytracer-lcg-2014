#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "PerfectSpecular.h"

namespace Raytracer {
  class Reflective: public Phong {

  public:
    Reflective();
    Reflective(const Reflective&);
    Reflective& operator= (const Reflective&);
    virtual Reflective* clone() const;
    ~Reflective();
    void set_kr(const double);
    void set_cr(const RGBColor&);
    void set_cr(double,double,double);
    virtual RGBColor shade(ShadeRec&);
    static Reflective* generic(RGBColor);
    static Reflective* generic_nodirect(RGBColor);
    static Reflective* generic_uncolored();

  private:
    PerfectSpecular* reflective_brdf;
  };


  inline void Reflective::set_kr(const double k) {
    reflective_brdf->set_kr(k);
  }


  inline void Reflective::set_cr(const RGBColor& c) {
    reflective_brdf->set_cr(c);
  }


  inline void Reflective::set_cr(double r, double g, double b) {
    reflective_brdf->set_cr(r, g, b);
  }
}

#endif
