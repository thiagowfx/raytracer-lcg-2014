#ifndef _VIEWPLANE_MINE_
#define _VIEWPLANE_MINE_

#include "BoostMine.hpp"
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
    bool operator==(const ViewPlane&) const;
    friend ostream& operator<<(ostream&, const ViewPlane&);

    /* Setters. */
    void set_hres(const unsigned);
    void set_vres(const unsigned);
    void set_pixel_size(const double);
    void set_gamma(const double);
    void set_out_of_gamut(const bool);
    void set_max_depth(const unsigned);

    /** Horizontal Image Resolution. */
    unsigned hres = 100;

    /** Vertical Image Resolution. */
    unsigned vres = 100;

    /** Pixel size. Decreasing means to zoom into the image. */
    double pixel_size = 1.0;

    /** Inverse of the gamma correction factor. */
    double inv_gamma = 1.0;

    /** If true, out of gamut colors will be displayed as red. */
    bool out_of_gamut = false;

    /** For reflective rays, the maximum number of bounces. */
    unsigned max_depth = 0;

    friend class boost::serialization::access;
    template<class Archive>
      void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(hres);
      ar & BOOST_SERIALIZATION_NVP(vres);
      ar & BOOST_SERIALIZATION_NVP(pixel_size);
      ar & BOOST_SERIALIZATION_NVP(inv_gamma);
      ar & BOOST_SERIALIZATION_NVP(out_of_gamut);
      ar & BOOST_SERIALIZATION_NVP(max_depth);
    }
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


  inline void ViewPlane::set_max_depth(const unsigned max_depth) {
    this->max_depth = max_depth;
  }
}

#endif // _VIEWPLANE_MINE_
