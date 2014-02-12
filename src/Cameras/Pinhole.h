#ifndef __PINHOLE__
#define __PINHOLE__

#include "World.h"    // we can #include "World.h" here
#include <Eigen/Dense>

using Eigen::Vector2d;

class Pinhole: public Camera {
  
 public:
  Pinhole();   							
  Pinhole(const Pinhole& ph);	
  virtual Camera* clone(void) const;			
  Pinhole& operator= (const Pinhole& rhs);	
  virtual ~Pinhole();   						
  void set_view_distance(const float vpd);
  void set_zoom(const float zoom_factor);
  Vector3D get_direction(const Vector2d& p) const;
  virtual void render_scene(const World& w);
		
 private:
  float	d;                      // view plane distance
  float	zoom;                   // zoom factor
		
};


inline void Pinhole::set_view_distance(float _d) {
  d = _d;
}	
	
inline void Pinhole::set_zoom(float zoom_factor) {
  zoom = zoom_factor;
}	

#endif
