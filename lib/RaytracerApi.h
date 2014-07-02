#ifndef _RAYTRACERAPI_MINE_
#define _RAYTRACERAPI_MINE_

#include "includes.h"

namespace Raytracer {

  class Api : public QObject {
      Q_OBJECT

  public:
    Api();
    ~Api();

  public slots:
    /******************* API *******************/
    /** ViewPlane: set horizontal resolution */
    void set_hres(int);

    /** ViewPlane: get horizontal resolution */
    int get_hres();

    /** ViewPlane: set vertical resolution */
    void set_vres(int);

    /** ViewPlane: get vertical resolution */
    int get_vres();

    /** Camera: render scene */
    // TODO
    void render_scene();

  public:
    // TODO
    const char* image="raytraced_image.png";

  private:
    void init();

    /******************* Private Members *******************/
    World* w;

  };
}

#endif // _RAYTRACERAPI_MINE_
