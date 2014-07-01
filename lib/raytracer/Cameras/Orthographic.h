#ifndef __ORTHOGRAPHIC__
#define __ORTHOGRAPHIC__

#include "Camera.h"
#include "World.h"

/* This uses ortographic viewing along the zw axis */
class Orthographic : public Camera {

 public:
  Orthographic();
  Orthographic(const Orthographic&);
  virtual ~Orthographic();
  virtual Orthographic* clone() const;
  virtual void render_scene(const World* w, const char* image_file);
};

#endif
