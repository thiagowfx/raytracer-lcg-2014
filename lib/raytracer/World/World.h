#ifndef _WORLD_MINE_
#define _WORLD_MINE_

#include "Ambient.h"
#include "Camera.h"
#include "GeometricObject.h"
#include "Light.h"
#include "RGBColor.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "ViewPlane.h"
#include <cstring> /* for png++ streerror */
#include <png++/png.hpp>
#include <vector>
using namespace std;

namespace Raytracer {
  class World {
  public:
    World();
    ~World();

    /** Camera. */
    Camera* camera_ptr = NULL;
    void set_camera(Camera*);

    /** Tracer. */
    Tracer* tracer_ptr = NULL;
    void set_tracer(Tracer*);

    /** Light sources. */
    vector<Light*> lights;
    void add_light(Light*); /**< Add a new light source. */
    void delete_lights(); /**< Delete all light sources. */

    /** Geometric Objects. */
    vector<GeometricObject*> objects;
    void add_object(GeometricObject*); /**< Add a new object. */
    void delete_objects(); /**< Delete all objects. */

    /** Background ambient light. */
    Ambient* ambient_ptr = new Ambient();
    void set_ambient_light(Ambient*);

    /** Background color. */
    RGBColor background_color = black;
    void set_background_color(RGBColor);

    ViewPlane vp;

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


  inline void World::set_camera(Camera* camera) {
    camera_ptr = camera;
  }


  inline void World::set_tracer(Tracer* tracer) {
    tracer_ptr = tracer;
  }


  inline void World::set_background_color(RGBColor color) {
    background_color = color;
  }
}

#endif // _WORLD_MINE_
