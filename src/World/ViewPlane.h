#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane {
  
 public:
  int    hres;   		// horizontal image resolution 
  int    vres;   		// vertical image resolution
  double s;			// pixel size --> decrease to zoom into the image
  double gamma;			// gamma correction factor
  bool   show_out_of_gamut;	// display red if RGBColor out of gamut
  int    num_samples;		// number of samples of the antialiasing
									
  ViewPlane(); 
  ~ViewPlane(); 
  ViewPlane(const ViewPlane& vp);
  ViewPlane& operator= (const ViewPlane& rhs);
						
  void set_hres(const int h_res);		
  void set_vres(const int v_res);				
  void set_pixel_size(const float size);		
  void set_gamma(const float g);		
  void set_show_of_gamut(const bool show);
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
}


inline void ViewPlane::set_show_of_gamut(const bool show) {
  show_out_of_gamut = show;
}


inline void ViewPlane::set_num_samples(const int num_samples) {
  this->num_samples = num_samples;
}


#endif
