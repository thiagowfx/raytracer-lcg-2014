#ifndef _RAYTRACERAPI_MINE_
#define _RAYTRACERAPI_MINE_

/* EIGEN */
#include <Eigen/Dense>
using Eigen::Vector3d;

/* RAYTRACER */
#include "Ambient.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "Directional.h"
#include "Emissive.h"
#include "Jittered.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "MultiJittered.h"
#include "Phong.h"
#include "PointLight.h"
#include "RGBColor.h"
#include "Ray.h"
#include "RaytracerApi.h"
#include "Reflective.h"
#include "Regular.h"
#include "ShadeRec.h"
#include "ViewPlane.h"
#include "World.h"

/* Geometric Objects */
#include "Plane.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Triangle.h"

/* Cameras */
#include "Orthographic.h"
#include "Pinhole.h"

/* Tracers */
#include "AreaLighting.h"
#include "MultipleObjects.h"
#include "Whitted.h"

/* Samplers */
#include "Hammersley.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "NRooks.h"
#include "PureRandom.h"
#include "Regular.h"

/* STL */
#include <cstdio>
#include <cmath>

/* PCS_DETECTION */
#include "PrimitivaDaniel.h"
#include "pc-shape-detection.h"

/* QT */
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMutex>
#include <QPalette>
#include <QSpinBox>
#include <QString>
#include <QStringListModel>

namespace Raytracer {

  /**
   * @brief Interface between QT GUI and Raytracer library. Provides getters and setters.
   */
  class Api : public QObject {
      Q_OBJECT

  public:
    /** Constructor. */
    Api();

    /** Destructor. */
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

    /** Tracer: set tracer type */
    void set_tracer_type(QString);

    /** Tracer: get tracer type */
    const char* get_tracer_type();

    /** Tracer: get tracer type model */
    QStringListModel* get_tracer_type_model();

    /** World: set background color */
    void set_background_color(QColor);

    /** World: get background color */
    QColor get_background_color();

    /** Camera: render scene */
    void render_scene();

    /** Get image file path. */
    const char* get_rendered_image();

  private:
    World* w;
  };
}

#endif // _RAYTRACERAPI_MINE_
