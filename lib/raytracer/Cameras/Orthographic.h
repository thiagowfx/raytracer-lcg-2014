#ifndef _ORTHOGRAPHIC_MINE_
#define _ORTHOGRAPHIC_MINE_

#include "Camera.h"
#include "World.h"

namespace Raytracer {
  /* This uses ortographic viewing along the zw axis */
  class Orthographic : public Camera {

  public:
    Orthographic();
    Orthographic(const Orthographic&);
    virtual ~Orthographic();
    virtual Orthographic* clone() const;
    virtual void render_scene(const World* w, const char* image_file);
  };
}

#endif // _ORTHOGRAPHIC_MINE_
