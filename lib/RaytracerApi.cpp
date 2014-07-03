#include "RaytracerApi.h"

namespace Raytracer {
  Api::Api() {
    init();
  }

  Api::~Api() {
    delete w;
  }

  void Api::set_hres(int hres) {
    w->vp.set_hres(hres);
  }

  int Api::get_hres() {
    return w->vp.hres;
  }

  void Api::set_vres(int vres) {
    w->vp.set_vres(vres);
  }

  int Api::get_vres() {
    return w->vp.vres;
  }

  void Api::set_pixel_size(double size) {
    w->vp.set_pixel_size(size);
  }

  double Api::get_pixel_size() {
    return w->vp.pixel_size;
  }

  void Api::set_gamma(double gamma)   {
    w->vp.set_gamma(gamma);
  }

  double Api::get_gamma() {
    return w->vp.gamma;
  }

  void Api::set_out_of_gamut(bool gamut) {
    w->vp.set_out_of_gamut(gamut);
  }

  bool Api::get_out_of_gamut() {
    return w->vp.out_of_gamut;
  }

  void Api::set_max_depth(int depth) {
    w->vp.set_max_depth(depth);
  }

  int Api::get_max_depth() {
    return w->vp.max_depth;
  }


  void Api::render_scene() {
    w->camera_ptr->render_scene(w, image);
  }

  void Api::init() {
    w = new World();

    /** Defaults */
    set_hres(400);
    set_vres(400);
    set_pixel_size(1.0);
    set_gamma(1.0);
    set_out_of_gamut(true);
    set_max_depth(1);
  }
}
