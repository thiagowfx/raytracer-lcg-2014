#ifndef _AMBIENTOCCLUDER_MINE_
#define _AMBIENTOCCLUDER_MINE_

#include "Ambient.h"
#include "Sampler.h"
#include "MultiJittered.h"
#include "World.h"

namespace Raytracer {
  /**
   * @brief It is like an ambient light, but it doesn't always
   * illuminate every object. This process depends on the sampling
   * technique used and the quantity of objects near the shaded
   * object.
   */
  class AmbientOccluder: public Ambient {
  public:
    AmbientOccluder();
    AmbientOccluder(const AmbientOccluder&);
    virtual Ambient* clone() const;
    virtual ~AmbientOccluder();
    virtual bool operator==(const AmbientOccluder&) const;

    virtual const char* to_string() const;
    virtual RGBColor L(ShadeRec&);
    bool in_shadow(const Ray&, ShadeRec&) const;
    virtual Vector3d get_direction(ShadeRec&);

    /* Setters. */
    void set_sampler(Sampler*);
    void set_minimum_amount(const double);

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Ambient);
      ar & BOOST_SERIALIZATION_NVP(minimum_amount);
      ar & BOOST_SERIALIZATION_NVP(u);
      ar & BOOST_SERIALIZATION_NVP(v);
      ar & BOOST_SERIALIZATION_NVP(w);
      // FIXME --> sampler_ptr
    }

  private:
    double minimum_amount = 0.30;
    Vector3d u = Vector3d::Zero();
    Vector3d v = Vector3d::Zero();
    Vector3d w = Vector3d::Zero();
    Sampler* sampler_ptr = NULL;
  };


  inline void AmbientOccluder::set_minimum_amount(const double) {
    this->minimum_amount = minimum_amount;
  }
}

#endif // _AMBIENTOCCLUDER_MINE_
