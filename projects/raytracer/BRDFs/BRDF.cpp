#include "BRDF.h"

BRDF::BRDF() :
  sampler_ptr(NULL)
{}


BRDF::BRDF(const BRDF& brdf) :
  sampler_ptr(NULL)
{
  if(brdf.sampler_ptr)
    sampler_ptr = brdf.sampler_ptr->clone();
}


BRDF& BRDF::operator= (const BRDF& rhs) {
  if (this != &rhs) {
    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }

    if (rhs.sampler_ptr)
      sampler_ptr = rhs.sampler_ptr->clone();
  }

  return *this;
}


BRDF::~BRDF() {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
}


void BRDF::set_sampler(Sampler* sPtr) {
  sampler_ptr = sPtr;
  sampler_ptr->map_samples_to_hemisphere(1); // for perfect diffuse
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const {
  return black;
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
  return black;
}
