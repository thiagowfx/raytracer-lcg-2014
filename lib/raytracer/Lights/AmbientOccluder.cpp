#include "AmbientOccluder.h"

AmbientOccluder::AmbientOccluder() :
  Ambient(),
  min_amount(0.25),
  u(Vector3d::Zero()),
  v(Vector3d::Zero()),
  w(Vector3d::Zero()),
  sampler_ptr(NULL)
{
  this->set_sampler(new MultiJittered(4));
}


AmbientOccluder::AmbientOccluder(const AmbientOccluder& a) :
  Ambient(a),
  min_amount(a.min_amount),
  u(a.u),
  v(a.v),
  w(a.w)
{
  // need to do a deep copy of the sampler
  if(a.sampler_ptr)
    sampler_ptr = a.sampler_ptr->clone();
}


Ambient* AmbientOccluder::clone() const {
  return new AmbientOccluder(*this);
}


AmbientOccluder& AmbientOccluder::operator=(const AmbientOccluder& rhs) {
  if (this != &rhs) {
    Light::operator= (rhs);
    min_amount = rhs.min_amount;
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;
    // need to do a deep copy of the sampler
    if(rhs.sampler_ptr != NULL) {
      sampler_ptr = rhs.sampler_ptr->clone();
    }
  }
  return *this;
}


AmbientOccluder::~AmbientOccluder () {}


Vector3d AmbientOccluder::get_direction(ShadeRec& sr) {
  Vector3d sp = sampler_ptr->sample_hemisphere();
  return (sp(0) * u) + (sp(1) * v) + (sp(2) * w);
}


void AmbientOccluder::set_sampler(Sampler* s_ptr) {
  if (sampler_ptr != NULL) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
  sampler_ptr = s_ptr;
  sampler_ptr->map_samples_to_hemisphere(1);
}


RGBColor AmbientOccluder::L(ShadeRec& sr) {
  w = sr.normal;
  v = w.cross(Vector3d(0.0072, 1.0, 0.0034)); // jitter the up vector in case normal is vertical
  v.normalize();
  u = v.cross(w);
  Ray shadow_ray(sr.hit_point, get_direction(sr));

  if (in_shadow(shadow_ray, sr))
    return min_amount * ls * color;
  else
    return ls * color;
}


bool AmbientOccluder::in_shadow(const Ray& ray, ShadeRec& sr) const {
  double t;
  const int num_objects = sr.w.objects.size();
  for (int j = 0; j < num_objects; j++)
    if (sr.w.objects[j]->hit(SHADOW_RAY, ray, t, sr))
      return true;
  return false;
}
