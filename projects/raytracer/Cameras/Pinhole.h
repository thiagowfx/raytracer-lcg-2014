#ifndef __PINHOLE__
#define __PINHOLE__

#include "Camera.h"
#include "World.h"

class Pinhole: public Camera {
  
 public:
  Pinhole();   							
  Pinhole(const Pinhole& ph);	
  Pinhole& operator= (const Pinhole& rhs);	
  virtual ~Pinhole();
  virtual Pinhole* clone() const;
  virtual void render_scene(const World* w, const char* image_file);

 private:
  Vector3d get_direction(const Vector2d& p) const;
};

#endif
