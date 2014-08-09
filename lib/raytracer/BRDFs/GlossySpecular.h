#ifndef _GLOSSYSPECULAR_MINE_
#define _GLOSSYSPECULAR_MINE_

#include "BRDF.h"

namespace Raytracer {
  /**
   * @brief Glossy specular reflection for direct and indirect illumination.
   */
  class GlossySpecular: public BRDF {
  public:
    GlossySpecular();
    GlossySpecular(const GlossySpecular&);
    ~GlossySpecular();
    virtual GlossySpecular* clone() const;
    virtual bool operator==(const GlossySpecular&) const;

    /** No sampling here: just the Phong formula. This is used for
        direct illumination only */
    virtual RGBColor f(const ShadeRec&, const Vector3d& wo, const Vector3d& wi) const;
    /** This is used for indirect illumination. */
    virtual RGBColor sample_f(const ShadeRec&, const Vector3d& wo, Vector3d& wi, double& pdf) const;

    /* Setters. */
    void set_ks(const double);
    void set_exp(const double);
    void set_cs(const RGBColor&);
    void set_normal(const Vector3d&);

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BRDF);
      ar & BOOST_SERIALIZATION_NVP(ks);
      ar & BOOST_SERIALIZATION_NVP(exp);
      ar & BOOST_SERIALIZATION_NVP(cs);
    }

  private:
    /** Specular (reflective) coefficient constant. */
    double ks = kKs;
    /** Specular exponent constant. */
    double exp = kExp;
    /** Specular (reflective) color. */
    RGBColor cs = white;
  };


  inline void GlossySpecular::set_ks(const double ks) {
    this->ks = ks;
  }


  inline void GlossySpecular::set_exp(const double exp) {
    this->exp = exp;
  }


  inline void GlossySpecular::set_cs(const RGBColor& cs) {
    this->cs = cs;
  }
}

#endif // _GLOSSYSPECULAR_MINE_
