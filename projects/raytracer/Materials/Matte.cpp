#include "Matte.h"

Matte::Matte () :
  Material(),
  ambient_brdf(new Lambertian),
  diffuse_brdf(new Lambertian)
{}


Matte::Matte(const Matte& m) :
  Material(m),
  ambient_brdf(NULL),
  diffuse_brdf(NULL)
{
  if(m.ambient_brdf)
    ambient_brdf = m.ambient_brdf->clone(); 
  if(m.diffuse_brdf)
    diffuse_brdf = m.diffuse_brdf->clone(); 
}


Material* Matte::clone() const {
  return new Matte(*this);
}	


Matte& Matte::operator= (const Matte& rhs) {
  if (this != &rhs) {		
    Material::operator=(rhs);
	
    if (ambient_brdf) {
      delete ambient_brdf;
      ambient_brdf = NULL;
    }

    if (rhs.ambient_brdf)
      ambient_brdf = rhs.ambient_brdf->clone();
		
    if (diffuse_brdf) {
      delete diffuse_brdf;
      diffuse_brdf = NULL;
    }

    if (rhs.diffuse_brdf)
      diffuse_brdf = rhs.diffuse_brdf->clone();
  }
  return *this;
}


Matte::~Matte() {
  if (ambient_brdf) {
    delete ambient_brdf;
    ambient_brdf = NULL;
  }
  if (diffuse_brdf) {
    delete diffuse_brdf;
    diffuse_brdf = NULL;
  }
}


RGBColor Matte::shade(ShadeRec& sr) {
  /** Direção para onde a luz sai (que é justamente o contrário de onde o raio primário da câmera vem */
  Vector3d wo = -sr.ray.d;

  /** Luz ambiente. Criada para simular, de maneira global, a iluminação difusa indireta.
   * Suposta constante para todos os objetos da cena. Modelo de campo isotrópico 3D.
   * rho = kd * cd, significa: o quanto o material reflete (entre 0 e 1) vezes a cor do material.
   * Adicionalmente: a cor da luz vezes a intensidade da luz.
   */
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

  const int num_lights = sr.w.lights.size();

  for (int j = 0; j < num_lights; j++) {
    /** Direção da onde a luz vem (tendência: apontar para *fora* do objeto!). Isso explica a convenção da luz direcional de especificar o contrário. */
    Vector3d wi = sr.w.lights[j]->get_direction(sr);    
    double ndotwi = sr.normal.dot(wi);
	
    if (ndotwi > 0.0) 
      /** f: constante de reflexão do material * a cor do material sobre pi (componente lambertiana difusa, refletindo igualmente para todos os lados)
       * L: intensidade da luz vezes a cor da luz
       *
       */
      L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
  }
  return L;
}

Matte *Matte::dummy(RGBColor color) {
  Matte* m = new Matte();
  m->set_ka(0.20);
  m->set_kd(0.80);
  m->set_cd(color);
  return m;
}


RGBColor Matte::get_color() const {
  return diffuse_brdf->get_cd();
}
