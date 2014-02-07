#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane {
 public:
  int 	hres;   		// horizontal image resolution 
  int 	vres;   		// vertical image resolution
  float	s;			// pixel size
  float	gamma;			// gamma correction factor
  float	inv_gamma;		// the inverse of the gamma correction factor
  bool	show_out_of_gamut;	// display red if RGBColor out of gamut
  int 	num_samples;		// number of samples of the antialiasing
									
 public:	
  ViewPlane();	  // default Constructor				
  ViewPlane(const ViewPlane& vp);	       // copy constructor
  ViewPlane& operator= (const ViewPlane& rhs); // assignment operator		
  ~ViewPlane();				       // destructor
						
  void set_hres(const int h_res);		
  void set_vres(const int v_res);				
  void set_pixel_size(const float size);		
  void set_gamma(const float g);		
  void set_gamut_display(const bool show);
  void set_num_samples(const int num_samples);
};

inline void ViewPlane::set_hres(const int h_res) {
  hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
  vres = v_res;
}

inline void ViewPlane::set_pixel_size(const float size) {
  s = size;
}

inline void ViewPlane::set_gamma(const float g) {
  gamma = g;
  inv_gamma = 1.0 / gamma;
}

inline void ViewPlane::set_gamut_display(const bool show) {
  show_out_of_gamut = show;
}

inline void ViewPlane::set_num_samples(const int num_samples) {
  this->num_samples = num_samples;
}

#endif
