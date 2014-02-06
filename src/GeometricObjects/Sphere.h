#ifndef __SPHERE__
#define __SPHERE__

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"

//-------------------------------------------------------------------------------- class Sphere

class Sphere: public GeometricObject {	
								  	
	public:
		
		Sphere(void);   									// Default constructor
				
		Sphere(Vector3d center, double r);					// Constructor 
					
		Sphere(const Sphere& sphere); 						// Copy constructor
		
		virtual Sphere* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~Sphere(void);   									

		Sphere& 											// assignment operator
		operator= (const Sphere& sphere);				
																					
		void
		set_center(const Vector3d& c);
		
		void
		set_center(const double x, const double y, const double z);
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;	
		
	private:
	
		Vector3d 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays
};



inline void
Sphere::set_center(const Vector3d& c) {
	center = c;
}
		
inline void
Sphere::set_center(const double x, const double y, const double z) {
  center(0) = x;
  center(1) = y;
  center(2) = z;
}
		
inline void
Sphere::set_radius(const double r) {
	radius = r;
}

#endif
