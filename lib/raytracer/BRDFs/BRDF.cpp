#include "BRDF.h"

namespace Raytracer {
  BRDF::BRDF() {}


  BRDF::BRDF(const BRDF& brdf) {
    if(brdf.sampler_ptr)
      sampler_ptr = brdf.sampler_ptr->clone();
    else
      sampler_ptr = NULL;
  }


  BRDF::~BRDF() {
    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }
  }


  void BRDF::set_sampler(Sampler* sampler) {
    this->sampler_ptr = sampler;
    /* For perfect diffuse. */
    sampler_ptr->map_samples_to_hemisphere(1);
  }


  RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi) const {
    return black;
  }


  RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3d& wo, Vector3d& wi, double& pdf) const {
    return black;
  }


  RGBColor BRDF::f(const ShadeRec &sr, const Eigen::Vector3d &wo, const Eigen::Vector3d &wi) const {
    return black;
  }


  RGBColor BRDF::rho(const ShadeRec &sr, const Eigen::Vector3d &wo) const {
    return black;
  }
}
