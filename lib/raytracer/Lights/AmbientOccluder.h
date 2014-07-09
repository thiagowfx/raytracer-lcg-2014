#ifndef __AMBIENTOCCLUDER__
#define __AMBIENTOCCLUDER__

#include "Ambient.h"
#include "Sampler.h"
#include "MultiJittered.h"
#include "World.h"

namespace Raytracer {
  class AmbientOccluder: public Ambient {
  public:
    AmbientOccluder();
    AmbientOccluder(const AmbientOccluder&);
    virtual Ambient* clone() const;
    virtual ~AmbientOccluder();
    virtual Vector3d get_direction(ShadeRec&);
    virtual RGBColor L(ShadeRec&);
    bool in_shadow(const Ray& ray, ShadeRec&) const;
    void set_sampler(Sampler*);
    void set_minimum_amount(const int);
    virtual const char* to_string() const;

  private:
    double minimum_amount = 0.30;
    Vector3d u = Vector3d::Zero();
    Vector3d v = Vector3d::Zero();
    Vector3d w = Vector3d::Zero();
    Sampler* sampler_ptr = NULL;
  };


  inline void AmbientOccluder::set_minimum_amount(const int) {
    this->minimum_amount = minimum_amount;
  }
}

#endif
