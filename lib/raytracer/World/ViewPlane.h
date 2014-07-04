#ifndef _VIEWPLANE_MINE_
#define _VIEWPLANE_MINE_

#include "MultiJittered.h"
#include "Regular.h"

/**
 * @brief Viewplane.
 */
class ViewPlane {
 public:
  ViewPlane();
  ViewPlane(const ViewPlane&);
  ~ViewPlane();

  int hres = 0; /**< Horizontal Image Resolution. */
  int vres = 0; /**< Vertical Image Resolution. */
  double pixel_size = 1.0; /**< Pixel Size. Decreasing means to zoom into the image. */
  double gamma = 1.0; /**< Gamma correction factor. */
  bool out_of_gamut = false; /**< If true, out of gamut colors will be displayed as red. */
  int max_depth = 1; /**< For reflective rays, the maximum number of bounces. */
  Sampler* sampler_ptr = NULL; /**< Sampler used for pixels. */

  void set_hres(const int);
  void set_vres(const int);
  void set_pixel_size(const double);
  void set_gamma(const double);
  void set_out_of_gamut(const bool);
  void set_max_depth(const int);
  void set_samples(int);
  void set_sampler(Sampler*);
};


inline void ViewPlane::set_hres(const int hres) {
  this->hres = hres;
}


inline void ViewPlane::set_vres(const int vres) {
  this->vres = vres;
}


inline void ViewPlane::set_pixel_size(const double pixel_size) {
  this->pixel_size = pixel_size;
}


inline void ViewPlane::set_gamma(const double gamma) {
  this->gamma = gamma;
}


inline void ViewPlane::set_out_of_gamut(const bool out_of_gamut) {
  this->out_of_gamut = out_of_gamut;
}


inline void ViewPlane::set_max_depth(const int depth) {
  this->max_depth = depth;
}


inline void ViewPlane::set_samples(int n) {
  if (n > 1) {
    set_sampler(new MultiJittered(n));
  }
  else {
    set_sampler(new Regular(1));
  }
}


inline void ViewPlane::set_sampler(Sampler* sp) {
  if (this->sampler_ptr) {
    delete this->sampler_ptr;
    this->sampler_ptr = NULL;
  }
  this->sampler_ptr = sp;
}

#endif // _VIEWPLANE_MINE_
