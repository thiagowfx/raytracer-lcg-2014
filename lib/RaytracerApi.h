#ifndef _RAYTRACERAPI_MINE_
#define _RAYTRACERAPI_MINE_

/* EIGEN */
#include <Eigen/Dense>
using Eigen::Vector3d;

#include "RGBColor.h"
#include "Ray.h"
#include "RaytracerApi.h"

/* Lights */
#include "Ambient.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "Directional.h"
#include "Light.h"
#include "PointLight.h"

/* Samplers */
#include "Jittered.h"
#include "MultiJittered.h"
#include "Regular.h"

/* Materials */
#include "Emissive.h"
#include "Material.h"
#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"

/* World */
#include "Camera.h"
#include "ShadeRec.h"
#include "ViewPlane.h"
#include "World.h"

/* Geometric Objects */
#include "Box.h"
#include "Disk.h"
#include "OpenCylinder.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Triangle.h"

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

    /******************* Utilities *******************/
    /** Convert from carthesian coordinates to spherical coordinates. */
    Vector3d carthesian_to_spherical(const Vector3d&);

    /** Convert from spherical coordinates to carthesian coordinates. */
    Vector3d spherical_to_carthesian(const Vector3d&);

    /** Convert from RGBColor to QColor. */
    QColor rgbcolor_to_qcolor(const RGBColor&);

    /** Convert from QColor to RGBColor. */
    RGBColor qcolor_to_rgbcolor(const QColor&);

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

    /** Camera: set carthesian coordinates for eye */
    void set_eye_carthesian(Vector3d);

    /** Camera: set carthesian coordinates for eye */
    void set_eye_carthesian(double,double,double);

    /** Camera: set spherical coordinates for eye, relatively */
    void set_eye_spherical_relatively(double,double,double);

    /** Get eye carthesian coordinates as (x, y, z) */
    const char* get_eye_carthesian_coordinates();

    /** Get eye spherical coordinates as (r, p, t) */
    const char* get_eye_spherical_coordinates();

    /** World: set ambient light type, color and radiance. */
    void set_ambient_light(QString, QColor, double);

    /** World: get ambient light type. */
    const char* get_ambient_light_type();

    /** World: get ambient light type model. */
    QStringListModel* get_ambient_light_type_model();

    /** World: get ambient light color. */
    QColor get_ambient_light_color();

    /** World: get ambient light radiance. */
    double get_ambient_light_radiance();

    /** World: set camera zoom. */
    void set_camera_zoom(double);

    /** World: get camera zoom. */
    double get_camera_zoom() const;

    /** World: set camera distance. */
    void set_camera_distance(double);

    /** World: get camera distance. */
    double get_camera_distance() const;

  private:
    World* w;
    char buffer[50];
  };
}

#endif // _RAYTRACERAPI_MINE_
