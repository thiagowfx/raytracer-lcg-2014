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

    /** ViewPlane: set pixel size */
    void set_pixel_size(double);

    /** ViewPlane: get pixel size */
    double get_pixel_size();

    /** ViewPlane: set gamma level */
    void set_gamma(double);

    /** ViewPlane: get gamma level */
    double get_gamma();

    /** ViewPlane: set show out of gamut colors */
    void set_out_of_gamut(bool);

    /** ViewPlane: get show out of gamut colors */
    bool get_out_of_gamut();

    /** ViewPlane: set max depth of reflections for secondary rays */
    void set_max_depth(int);

    /** ViewPlane: get max depth of reflections for secondary rays */
    int get_max_depth();

    /** ViewPlane: set sampler type and number of samples */
    void set_sampler(QString, int);

    /** ViewPlane: get number of samples */
    int get_number_of_samples();

    /** ViewPlane: get sampler type name */
    const char* get_sampler_type();

    /** ViewPlane: get sampler type model */
    QStringListModel* get_sampler_type_model();

    /** Camera: render scene */
    // TODO
    void render_scene();

    const char* get_rendered_image();

  public:
    // TODO

  private:
    void init();

    /******************* Private Members *******************/
    World* w;
  };
}

#endif // _RAYTRACERAPI_MINE_
