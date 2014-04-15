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
  void set_view_distance(const double d);
  void set_zoom(const double zoom);
  Vector3d get_direction(const Vector2d& p) const;
  virtual void render_scene(const World* w, const char* image_file);
		
 private:
  double	d;                      // view plane distance
  double	zoom;                   // zoom factor

};


inline void Pinhole::set_view_distance(const double d) {
  this->d = d;
}	


inline void Pinhole::set_zoom(const double zoom) {
  this->zoom = zoom;
}	

#endif
