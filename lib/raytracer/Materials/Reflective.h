#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "PerfectSpecular.h"

namespace Raytracer {
  /**
   * @brief A reflective material is like a Phong one, however it also
   * supports light reflections.
   */
  class Reflective: public Phong {
  public:
    /** Construct a new uncolored, black-ish, Reflective material,
     * assimiling a pure mirror, with only reflections.
     */
    Reflective();
    /**
     * Construct a new Reflective material with the given color
     * (direct illumination + reflective illumination + reflections)
     */
    Reflective(const RGBColor&);
    Reflective(const Reflective&);
    virtual Reflective* clone() const;
    ~Reflective();
    virtual bool operator==(const Reflective&) const;

    virtual RGBColor shade(ShadeRec&);
    virtual RGBColor area_light_shade(ShadeRec&);

    /* Setters. */
    void set_kr(const double);
    void set_cr(const RGBColor&);

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Phong);
      ar & BOOST_SERIALIZATION_NVP(reflective_brdf);
    }

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
