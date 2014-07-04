#ifndef _PINHOLE_MINE_
#define _PINHOLE_MINE_

#include "Camera.h"
#include "World.h"

namespace Raytracer {
  class Pinhole: public Camera {

  public:
    Pinhole();
    Pinhole(const Pinhole& ph);
    virtual ~Pinhole();
    virtual Pinhole* clone() const;
    virtual void render_scene(const World* w, const char* image_file);

  private:
    /** Return a vector which has eye and p as its ends. */
    Vector3d get_direction(const Vector2d& p) const;
  };
}

#endif // _PINHOLE_MINE_
