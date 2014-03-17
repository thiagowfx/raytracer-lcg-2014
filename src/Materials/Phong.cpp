#include "Phong.h"


Phong::Phong():
  Material (),
  ambient_brdf (new Lambertian),
  diffuse_brdf (new Lambertian),
  specular_brdf (new GlossySpecular)
{}


Phong::~Phong() {}


Material* Phong::clone() const {
  return new Phong(*this);
}


RGBColor Phong::shade (ShadeRec& sr) {
  Vector3d wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho (sr,wo) * sr.w.ambient_ptr->L(sr);
  int num_lights = sr.w.lights.size();

  for (int i = 0; i < num_lights; ++i) {
    Vector3d wi = -sr.w.lights[i]->get_direction(sr);
    float ndotwi = sr.normal.dot(wi);
    if (ndotwi > 0.0) {
      // bool in_shadow = false;
      // if (sr.w.render_ptr->render_shadow) {
        // Ray shadow_ray(sr.hit_point, wi);
        // in_shadow = sr.w.lights[i]->in_shadow (shadow_ray, sr);
      // }
      //if (in_shadow) OutputDebugString ("Hit\n");
      // if (!in_shadow)
      L+= (diffuse_brdf->f(sr,wo,wi) + specular_brdf->f(sr,wo,wi)) * sr.w.lights[i]->L(sr) * ndotwi;
    }
  }
  
  return L;
}
