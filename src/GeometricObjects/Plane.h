#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.h"

//-------------------------------------------------------------------- class Plane

class Plane: public GeometricObject {
	
	public:
	
		Plane(void);   												// default constructor
		
		Plane(const Vector3d& point, const Vector3d& normal);			// constructor	
	
		Plane(const Plane& plane); 									// copy constructor
		
		virtual Plane* 												// virtual copy constructor
		clone(void) const;

		Plane& 														// assignment operator
		operator= (const Plane& rhs);	
		
		virtual														// destructor
		~Plane(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	private:
	
		Vector3d 	a;   				// point through which plane passes 
		Vector3d	n;					// normal to the plane
				
		static const double kEpsilon;   // for shadows and secondary rays
};

#endif
