#ifndef __AMBIENTOCCLUDER__
#define __AMBIENTOCCLUDER__

#include "Ambient.h"
#include "Sampler.h"
#include "MultiJittered.h"
#include "World.h"

class AmbientOccluder: public Ambient {

public:
  AmbientOccluder();
  AmbientOccluder(const AmbientOccluder& a);
  virtual Ambient* clone() const;
  AmbientOccluder& operator=(const AmbientOccluder& rhs);
  virtual ~AmbientOccluder();
  virtual Vector3d get_direction(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& s);
  bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
  void set_sampler(Sampler* s_ptr);
  void set_min_amount(int n);

private:
  double		min_amount;
  Vector3d	u, v, w;
  Sampler*	sampler_ptr;
};


inline void AmbientOccluder::set_min_amount(int n) {
  min_amount = n;
}

#endif
