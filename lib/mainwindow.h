#ifndef _MAINWINDOW_MINE_
#define _MAINWINDOW_MINE_

#include "RaytracerApi.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  /* Callbacks are a simple way to create QT events. */
  void sampler_callback();
  void background_color_callback();
  void ambient_light_color_callback();
  void ambient_light_callback();

  /** Auto render image after changing any option if the corresponding member
   * variable is set. */
  void auto_render_callback();

  /******************* Actions ******************/

  /** Quit from the application. */
  void on_actionQuit_triggered();

  /** Show about qt dialog. */
  void on_actionAbout_Qt_triggered();

  /* Render the image then displays it, also updating the statusbar. */
  void on_actionRender_scene_triggered();

  /** Open a dialog to export the rendered image. */
  void on_actionExport_Image_triggered();

  /** Zoom into the image. */
  void on_actionZoom_In_triggered();

  /** Zoom out of the image. */
  void on_actionZoom_Out_triggered();

  /** Reset zoom of the image to 1.0x. */
  void on_actionZoom_Reset_triggered();

private:
  /** QT GUI interface. */
  Ui::MainWindow *ui;

  /** Bind keys to events. */
  bool event_filter(QObject *object, QEvent *event);

  /** Is the rendering process in progress? */
  QMutex in_progress_mutex;

  /** Communication with the raytracer library. */
  Raytracer::Api *api;

  /** Update zoom level label. */
  void update_zoom_level_label();

  /** Update carthesian coordinates label from the eye position. */
  void update_eye_carthesian_label();

  /** Update spherical coordinates label from the eye position. */
  void update_eye_spherical_label();

  /** Is the rendering process in progress? */
  QLabel *status_in_progress_label;

  /** Time spent to render the last scene. */
  QLabel *status_rendering_time;

  /** Auto render image after changing any option? */
  QCheckBox *auto_render_checkbox;
};

#endif // _MAINWINDOW_MINE_
