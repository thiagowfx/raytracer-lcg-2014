#include "GeometricObject.h"

namespace Raytracer {
  GeometricObject::GeometricObject() {}


  GeometricObject::GeometricObject (const GeometricObject& object) :
    shadows(object.shadows) {
    if (object.material_ptr)
      material_ptr = object.material_ptr->clone();
    else
      material_ptr = NULL;
  }


  GeometricObject::~GeometricObject () {
    if (material_ptr) {
      delete material_ptr;
      material_ptr = NULL;
    }
  }


  void GeometricObject::set_material(Material* mPtr) {
    material_ptr = mPtr;
  }


  Vector3d GeometricObject::sample() {
    return Vector3d::Zero();
  }


  double GeometricObject::pdf(const ShadeRec &sr) {
    return 0.0;
  }


  Vector3d GeometricObject::get_normal(const Eigen::Vector3d &p) {
    return Vector3d::Zero();
  }


  void GeometricObject::set_shadows(const bool shadow){
    shadows = shadow;
  }


  bool GeometricObject::get_shadows() const {
    return shadows;
  }
}
