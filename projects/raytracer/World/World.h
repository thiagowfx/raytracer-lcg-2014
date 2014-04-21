#ifndef __WORLD__
#define __WORLD__

/* This file contains the declaration of the class World
   The World class does not have a copy constructor or an assignment operator, for the followign reasons:
   
   1 	There's no need to copy construct or assign the World
   2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
   3 	These operations wouldn't work because the world is self-referencing:
   the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
   Tracer class, the World copy construtor would call itself recursively until we ran out of memory. */

#include "Ambient.h"
#include "Camera.h"
#include "Constants.h"
#include "GeometricObject.h"
#include "Light.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "ViewPlane.h"
#include <cstdio>
#include <cstring>              /* for png++ streerror */
#include <png++/png.hpp>
#include <vector>
using namespace std;

class World {
 
 public:	
  ViewPlane                vp;
  RGBColor                 background_color;
  Tracer*                  tracer_ptr;
  Ambient*                 ambient_ptr;
  Camera*                  camera_ptr;		
  vector<GeometricObject*> objects;		
  vector<Light*>           lights;
		
  World();
  ~World();
  void add_object(GeometricObject*);
  void add_light(Light*); 
  void set_ambient_light(Ambient*);
  void set_camera(Camera*);	 
  void display_pixel(const int row, const int column, const RGBColor& pixel_color, png::image<png::rgb_pixel>& image) const;
  ShadeRec hit_bare_bones_objects(const Ray&);
  ShadeRec hit_objects(const Ray&);
						
 private:
  void delete_objects();
  void delete_lights();  
};


inline void World::add_object(GeometricObject* object_ptr) {  
  objects.push_back(object_ptr);	
}


inline void World::add_light(Light* light_ptr) {  
  lights.push_back(light_ptr);
}


inline void World::set_ambient_light(Ambient* light_ptr) {
  ambient_ptr = light_ptr;
}


inline void World::set_camera(Camera* c_ptr) {
  camera_ptr = c_ptr;
}

#endif
