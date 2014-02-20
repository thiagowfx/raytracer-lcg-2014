#ifndef __WORLD__
#define __WORLD__

// The World class does not have a copy constructor or an assignment operator, for the followign reasons:
// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include "Camera.h"
#include "Light.h"
#include "Constants.h"
#include "GeometricObject.h"
#include "MultipleObjects.h"
#include "Plane.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Sphere.h"
#include "Tracer.h"
#include "ViewPlane.h"
#include <Eigen/Dense>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <png++/png.hpp>
#include <vector>
using Eigen::Vector2d;
using Eigen::Vector3d;
using namespace std;

class World {
  
 public:	
  ViewPlane                vp;
  RGBColor                 background_color;
  Tracer*                  tracer_ptr;
  Light*                   ambient_ptr;
  Camera*                  camera_ptr;
  vector<GeometricObject*> objects;
  vector<Light*>           lights;
		
  World(); 
  ~World();
  void add_object(GeometricObject* object_ptr);
  void add_light(Light* light_ptr);
  void set_ambient_light(Light* light_ptr);			
  void set_camera(Camera* c_ptr);	 
  void build();
  void render_scene(FILE *fp) const;
  RGBColor max_to_one(const RGBColor& c) const;
  RGBColor clamp_to_color(const RGBColor& c) const;
  void display_pixel(const int row, const int column, const RGBColor& pixel_color, FILE *fp) const;
  ShadeRec hit_objects(const Ray& ray);
  void file_to_png(FILE *fp, const char *imageFile);
						
 private:
  void delete_objects();
  void delete_lights();
  
};


inline void World::add_object(GeometricObject* object_ptr) {  
  objects.push_back(object_ptr);	
}


inline void World::set_ambient_light(Light* light_ptr) {
  ambient_ptr = light_ptr;
}


inline void World::set_camera(Camera* c_ptr) {
  camera_ptr = c_ptr;
}

#endif
