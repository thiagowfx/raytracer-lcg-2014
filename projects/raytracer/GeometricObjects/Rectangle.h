#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "Sampler.h"
#include "GeometricObject.h"

class Rectangle: public GeometricObject {	
	public:
		
		Rectangle();   									
		Rectangle(const Vector3d& _p0, const Vector3d& _a, const Vector3d& _b);
		Rectangle(const Vector3d& _p0, const Vector3d& _a, const Vector3d& _b, const Vector3d& n);
		virtual Rectangle* clone() const;
    Rectangle(const Rectangle& r); 						
		virtual ~Rectangle();   									
		Rectangle& operator= (const Rectangle& rhs);
		// BBox get_bounding_box();				
		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;	
    virtual bool shadow_hit(const Ray& ray, double& tmin) const;
		
		/* the following functions are used when the rectangle is a light source */
		virtual void set_sampler(Sampler* sampler); 
		virtual Vector3d sample();
		virtual double pdf(ShadeRec& sr);
		virtual Vector3d get_normal(const Vector3d& p);		
		
	private:
		Vector3d 		p0;   		// corner vertex 
		Vector3d		a;				// side
		Vector3d		b;				// side
		double			a_len_squared;	// square of the length of side a
		double			b_len_squared;	// square of the length of side b
		Vector3d		normal;	
		double			area;             // for rectangular lights
		double			inv_area;         // for rectangular lights
		Sampler*		sampler_ptr;    // for rectangular lights 	
};

#endif
