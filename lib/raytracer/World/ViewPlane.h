#ifndef _VIEWPLANE_MINE_
#define _VIEWPLANE_MINE_

#include "Regular.h"

namespace Raytracer {
  /**
   * @brief Stores information such as image resolution, image details and color adjustments.
   */
  class ViewPlane {
  public:
    ViewPlane();
    ~ViewPlane();
    ViewPlane(const ViewPlane&);

    /* Setters. */
    void set_hres(const unsigned);
    void set_vres(const unsigned);
    void set_pixel_size(const double);
    void set_gamma(const double);
    void set_out_of_gamut(const bool);
    void set_max_depth(const int);
    void set_sampler(Sampler*);

    /** Horizontal Image Resolution. */
    int hres = 100;

    /** Vertical Image Resolution. */
    int vres = 100;

    /** Pixel size. Decreasing means to zoom into the image. */
    double pixel_size = 1.0;
    
    /** Inverse of the gamma correction factor. */
    double inv_gamma = 1.0;
    
    /** If true, out of gamut colors will be displayed as red. */
    bool out_of_gamut = false;

    /** For reflective rays, the maximum number of bounces. */
    int max_depth = 1;

    /** Sampler for pixels. */
    Sampler* sampler_ptr = new Regular(1);
  };


  inline void ViewPlane::set_hres(const unsigned hres) {
    this->hres = hres;
  }


  inline void ViewPlane::set_vres(const unsigned vres) {
    this->vres = vres;
  }


  inline void ViewPlane::set_pixel_size(const double pixel_size) {
    this->pixel_size = pixel_size;
  }


  inline void ViewPlane::set_gamma(const double gamma) {
    this->inv_gamma = 1.0 / gamma;
  }


  inline void ViewPlane::set_out_of_gamut(const bool out_of_gamut) {
    this->out_of_gamut = out_of_gamut;
  }


  inline void ViewPlane::set_max_depth(const int max_depth) {
    this->max_depth = max_depth;
  }


  inline void ViewPlane::set_sampler(Sampler* sp) {
    if (this->sampler_ptr) {
      delete this->sampler_ptr;
      this->sampler_ptr = NULL;
    }
    this->sampler_ptr = sp;
  }
}

#endif // _VIEWPLANE_MINE_
