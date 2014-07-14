#include "Phong.h"

namespace Raytracer {
  Phong::Phong():
    Material ()
  {}


  Phong::~Phong() {
    if (ambient_brdf) {
      delete ambient_brdf;
      ambient_brdf = NULL;
    }

    if (diffuse_brdf) {
      delete diffuse_brdf;
      diffuse_brdf = NULL;
    }

    if (specular_brdf) {
      delete specular_brdf;
      specular_brdf = NULL;
    }
  }


  Phong::Phong(const Phong& m) :
    Material(m) {
    if (m.ambient_brdf)
      ambient_brdf = m.ambient_brdf->clone();
    else
      ambient_brdf = NULL;

    if (m.diffuse_brdf)
      diffuse_brdf = m.diffuse_brdf->clone();
    else
      diffuse_brdf = NULL;

    if (m.specular_brdf)
      specular_brdf = m.specular_brdf->clone();
    else
      specular_brdf = NULL;
  }


  Material* Phong::clone() const {
    return new Phong(*this);
  }


  RGBColor Phong::shade (ShadeRec& sr) {
    Vector3d wo    = -sr.ray.direction;
    RGBColor L = ambient_brdf->rho (sr,wo) * sr.w.ambient_ptr->L(sr);
    const int num_lights = sr.w.lights.size();

    for (int j = 0; j < num_lights; ++j) {
      Vector3d wi = sr.w.lights[j]->get_direction(sr);
      double ndotwi = sr.normal.dot(wi);

      if (ndotwi > 0.0) {
        bool in_shadow = false;

        if (sr.w.lights[j]->casts_shadows()) {
          Ray shadow_ray(sr.hit_point, wi);
          in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
        }
        if (!in_shadow) {
          L+= (diffuse_brdf->f(sr,wo,wi) + specular_brdf->f(sr,wo,wi)) * sr.w.lights[j]->L(sr) * ndotwi;
	}
      }
    }

    return L;
  }

  RGBColor Phong::area_light_shade(ShadeRec &sr) {
    Vector3d wo    = -sr.ray.direction;
    RGBColor L     = ambient_brdf->rho (sr,wo) * sr.w.ambient_ptr->L(sr);
    const int num_lights = sr.w.lights.size();

    for (int j = 0; j < num_lights; ++j) {
      Vector3d wi = sr.w.lights[j]->get_direction(sr);
      double ndotwi = sr.normal.dot(wi);

      if (ndotwi > 0.0) {
        bool in_shadow = false;

        if (sr.w.lights[j]->casts_shadows()) {
          Ray shadow_ray(sr.hit_point, wi);
          in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
        }
        if (!in_shadow) {
          L+= (diffuse_brdf->f(sr,wo,wi) + specular_brdf->f(sr,wo,wi)) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
	}
      }
    }
    return L;
  }


  Phong* Phong::generic(RGBColor color) {
    Phong* p = new Phong();
    p->set_ka(kKa);
    p->set_kd(kKd);
    p->set_cd(color);
    p->set_ks(kKs);
    p->set_cs(color);
    p->set_exp(kExp);
    return p;
  }


  RGBColor Phong::get_color() const {
    return diffuse_brdf->get_cd();
  }
}
