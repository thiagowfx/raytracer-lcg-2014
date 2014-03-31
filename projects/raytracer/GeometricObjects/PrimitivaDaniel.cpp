#include "PrimitivaDaniel.h"


PrimitivaDaniel::PrimitivaDaniel() :
  GeometricObject(),
  primitive()
{}


PrimitivaDaniel::PrimitivaDaniel(Primitive* p) :
  GeometricObject(),
  primitive(p)
{}


PrimitivaDaniel::~PrimitivaDaniel() {
  if (primitive) {
    delete primitive;
    primitive = NULL;
  }
}


bool PrimitivaDaniel::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  Vector3d intersectionPoint;
  Vector3d intersectionNormal;
  bool hit = false;

  // for (unsigned int i = 0; i < primitives.size(); ++i) {

  //   if (primitives[i]->rayIntersection(ray.o, ray.d, intersectionPoint, intersectionNormal)) {
  //     hit = true;
  //     sr.local_hit_point = intersectionPoint;
  //     sr.normal = intersectionNormal;
  //   }
  // }

  // if (hit) {
  //   s = sr;
  // }

  return hit;
}
