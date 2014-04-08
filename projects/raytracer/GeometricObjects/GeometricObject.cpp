#include "GeometricObject.h"

GeometricObject::GeometricObject() :
  material_ptr(NULL),
  color()
{}


GeometricObject::GeometricObject (const GeometricObject& object) :
  material_ptr(NULL),
  color(object.color)
{
  if (object.material_ptr)
    material_ptr = object.material_ptr->clone();
}	


GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
  
  if (this != &rhs) {    
    if (material_ptr) {
      delete material_ptr;
      material_ptr = NULL;
    }

    if (rhs.material_ptr)
      material_ptr = rhs.material_ptr->clone();
  }

  return *this;
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
