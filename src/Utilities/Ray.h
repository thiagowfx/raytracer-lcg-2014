#ifndef __RAY__
#define __RAY__

#include <Eigen/Dense>

using Eigen::Vector3d;

class Ray {
 public:
	
  Vector3d	o;		// origin 
  Vector3d	d; 		// direction 
  Ray(void);					
  Ray(const Vector3d& origin, const Vector3d& dir);	
  Ray(const Ray& ray); 		
  Ray& operator= (const Ray& rhs);		 								
  ~Ray(void);
};

#endif
