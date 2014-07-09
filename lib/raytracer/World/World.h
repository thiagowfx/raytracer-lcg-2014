#ifndef _WORLD_MINE_
#define _WORLD_MINE_

#include "Ambient.h"
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
  /**
   * @brief Stores all objects and lights, and contains helper objects, such as camera, tracer and ambient light.
   */
  class Camera;
  class World {
  public:
    World();
    ~World();

    /* Setters. */
    void set_camera(Camera*);
    void set_tracer(Tracer*);
    void set_ambient_light(Ambient*);
    void set_background_color(RGBColor);
    void add_light(Light*);
    void add_object(GeometricObject*);

    /** Camera. */
    Camera* camera_ptr = NULL;

    /** Tracer. */
    Tracer* tracer_ptr = NULL;

    /** Light sources. */
    vector<Light*> lights;

    /** Delete all light sources. */
    void delete_lights();
    
    /** Geometric Objects. */
    vector<GeometricObject*> objects;

    /** Delete all objects. */
    void delete_objects();
    
    /** Background ambient light. */
    Ambient* ambient_ptr = new Ambient();

    /** Background color. */
    RGBColor background_color = black;

    /** Viewplane. */
    ViewPlane vp;

    /** Update image pixel with the given color. */
    void display_pixel(const int row,
                       const int column,
                       const RGBColor& pixel_color,
                       png::image<png::rgb_pixel>& image) const;
    
    /** Try to hit objects with the ray, filling just bare bones information in the ShadeRec object. */
    ShadeRec hit_bare_bones_objects(const Ray&);

    /** Try to hit objects with the ray, filling information in the ShadeRec object. */
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
    if (tracer_ptr != NULL) {
      delete tracer_ptr;
      tracer_ptr = NULL;
    }
    tracer_ptr = tracer;
  }


  inline void World::set_background_color(RGBColor color) {
    background_color = color;
  }
}

#endif // _WORLD_MINE_
