#ifndef _WORLD_MINE_
#define _WORLD_MINE_

#include "Ambient.h"
#include "Camera.h"
#include "Utilities.h"
#include "GeometricObject.h"
#include "Light.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "ViewPlane.h"
#include <cstdio>
#include <cstring> /* for png++ streerror */
#include <png++/png.hpp>
#include <vector>
using namespace std;

class World {
 public:
  World();
  ~World();

  Raytracer::Camera* camera_ptr = NULL; /**< Camera. */
  void set_camera(Raytracer::Camera*);

  vector<Light*> lights;
  void add_light(Light*); /**< Add a new light source. */
  void delete_lights(); /**< Delete all light sources. */

  vector<GeometricObject*> objects;
  void add_object(GeometricObject*); /**< Add a new object. */
  void delete_objects(); /**< Delete all objects. */

  Ambient* ambient_ptr = new Ambient();
  void set_ambient_light(Ambient*);

  Tracer* tracer_ptr = NULL; /**< Raytracer. */
  void set_tracer(Tracer*);

  ViewPlane vp;
  RGBColor background_color = black; /**< Background color. */
  void display_pixel(const int row, const int column, const RGBColor& pixel_color, png::image<png::rgb_pixel>& image) const;
  ShadeRec hit_bare_bones_objects(const Ray&);
  ShadeRec hit_objects(const Ray&);
};


inline void World::add_object(GeometricObject* object_ptr) {
  objects.push_back(object_ptr);
}


inline void World::add_light(Light* light_ptr) {
  lights.push_back(light_ptr);
}


inline void World::set_ambient_light(Ambient* light_ptr) {
  if (ambient_ptr != NULL) {
    delete ambient_ptr;
    ambient_ptr = NULL;
  }
  ambient_ptr = light_ptr;
}


inline void World::set_camera(Raytracer::Camera* camera) {
  camera_ptr = camera;
}


inline void World::set_tracer(Tracer* tracer) {
  tracer_ptr = tracer;
}

#endif // _WORLD_MINE_
