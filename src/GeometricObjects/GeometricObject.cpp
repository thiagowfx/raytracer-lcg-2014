#include "Constants.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject(void)
  : 	color(black)
{}


GeometricObject::GeometricObject (const GeometricObject& object)
  : 	color(object.color)
{}	


GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	
  if (this != &rhs) {
    color = rhs.color;
  }

  return (*this);
}


GeometricObject::~GeometricObject (void) {}
