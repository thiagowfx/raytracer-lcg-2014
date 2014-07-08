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
    AmbientOccluder(const AmbientOccluder& a);
    virtual Ambient* clone() const;
    virtual ~AmbientOccluder();
    virtual Vector3d get_direction(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& s);
    bool in_shadow(const Ray& ray, ShadeRec& sr) const;
    void set_sampler(Sampler* s_ptr);
    void set_minimum_amount(int n);
    virtual const char* to_string() const;

  private:
    double minimum_amount = 0.30;
    Vector3d u = Vector3d::Zero();
    Vector3d v = Vector3d::Zero();
    Vector3d w = Vector3d::Zero();
    Sampler* sampler_ptr = NULL;
  };


  inline void AmbientOccluder::set_minimum_amount(int minimum_amount) {
    this->minimum_amount = minimum_amount;
  }
}

#endif
