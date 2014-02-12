// This file contains the definition of the Camera class

#include "Camera.h"
#include <Eigen/Dense>

using Eigen::Vector3d;


Camera::Camera(void)		
  :	eye(0, 0, 500),
        lookat(Vector3d::Zero()),
        ra(0),
        u(1, 0, 0),
        v(0, 1, 0),
        w(0, 0, 1),
        up(0, 1, 0),
        exposure_time(1.0)
{}


Camera::Camera(const Camera& c)   		
  : 	eye(c.eye),
        lookat(c.lookat),
        ra(c.ra),
        u(c.u),
        v(c.v),
        w(c.w),
        up(c.up),
        exposure_time(c.exposure_time)
{}


Camera& Camera::operator= (const Camera& rhs) {
  if (this == &rhs)
    return (*this);
	
  eye				= rhs.eye;
  lookat			= rhs.lookat;
  ra				= rhs.ra;
  up				= rhs.up;
  u				= rhs.u;
  v				= rhs.v;
  w				= rhs.w;
  exposure_time 	= rhs.exposure_time;

  return (*this);
}


Camera::~Camera(void) {}



//-------------------------------------------------------------- compute_uvw

// This computes an orthornormal basis given the view point, lookat point, and up vector

void
Camera::compute_uvw(void) {
  w = eye - lookat;
  w.normalize();
  u = up ^ w; 
  u.normalize();
  v = w ^ u;

  // take care of the singularity by hardwiring in specific camera orientations
	
  if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
    u = Vector3d(0, 0, 1);
    v = Vector3d(1, 0, 0);
    w = Vector3d(0, 1, 0);	
  }
	
  if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
    u = Vector3d(1, 0, 0);
    v = Vector3d(0, 0, 1);
    w = Vector3d(0, -1, 0);
  }
}


