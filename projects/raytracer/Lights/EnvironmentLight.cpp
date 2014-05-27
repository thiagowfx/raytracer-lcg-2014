#include "EnvironmentLight.h"

EnvironmentLight::EnvironmentLight() :
  Light(),
  sampler_ptr(NULL),
  material_ptr(NULL),
  u(Vector3d::Zero()), v(Vector3d::Zero()), w(Vector3d::Zero()),
  wi(Vector3d::Zero())
{}


EnvironmentLight::EnvironmentLight(const EnvironmentLight& el) :
  Light(el),
  u(el.u), v(el.v), w(el.w),
  wi(el.wi)
{
  if(el.sampler_ptr)
    sampler_ptr = el.sampler_ptr->clone();
  else
    sampler_ptr = NULL;

  if(el.material_ptr)
    material_ptr = el.material_ptr->clone();
  else
    material_ptr = NULL;
}


Light* EnvironmentLight::clone() const {
  return new EnvironmentLight(*this);
}


EnvironmentLight::~EnvironmentLight() {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }

  if (material_ptr) {
    delete material_ptr;
    material_ptr = NULL;
  }
}


EnvironmentLight& EnvironmentLight::operator= (const EnvironmentLight& rhs) {
  if (this != &rhs) {
    Light::operator=(rhs);

    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }

    if (rhs.sampler_ptr)
      sampler_ptr = rhs.sampler_ptr->clone();

    if (material_ptr) {
      delete material_ptr;
      material_ptr = NULL;
    }

    if (rhs.material_ptr)
      material_ptr = rhs.material_ptr->clone();
  }
  return *this;
}


Vector3d EnvironmentLight::get_direction(ShadeRec& sr) {
  w = sr.normal;
  v = Vector3d(0.0034, 1, 0.0071).cross(w);
  v.normalize();
  u = v.cross(w);
  Vector3d sp = sampler_ptr->sample_hemisphere();
  wi = sp(0) * u + sp(1) * v + sp(2) * w;
  return wi;
}


void EnvironmentLight::set_material(Material* mat_ptr) {
  material_ptr = mat_ptr;
}


void EnvironmentLight::set_sampler(Sampler* s_ptr) {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
  sampler_ptr = s_ptr;
  sampler_ptr->map_samples_to_hemisphere(1);
}


RGBColor EnvironmentLight::L(ShadeRec& sr) {
  return material_ptr->get_Le(sr);
}


// Page 343: this should be the same as AmbientOccluder
bool EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
  double t;
  const int num_objects = sr.w.objects.size();
  for (int j = 0; j < num_objects; j++)
    if (sr.w.objects[j]->shadow_hit(ray, t))
      return true;
  return false;
}


/* The following function is not in the book. It uses Equation 18.6 */
double EnvironmentLight::pdf(const ShadeRec& sr) const {
  return sr.normal.dot(wi) * (1.0 / M_PI);
}
