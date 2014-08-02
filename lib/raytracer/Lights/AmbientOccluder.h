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

    virtual const char* to_string() const;
    virtual RGBColor L(ShadeRec&);
    bool in_shadow(const Ray&, ShadeRec&) const;
    virtual Vector3d get_direction(ShadeRec&);

    /* Setters. */
    void set_sampler(Sampler*);
    void set_minimum_amount(const double);
    
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
