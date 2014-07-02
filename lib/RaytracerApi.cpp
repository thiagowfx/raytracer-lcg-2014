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

  void Api::render_scene() {
    w->camera_ptr->render_scene(w, image);
  }

  void Api::init() {
    w = new World();
    set_hres(400);
    set_vres(400);
  }
}
