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
  void samplerCallback();
  void backgroundColorCallback();
  void ambientLightColorCallback();
  void ambientLightCallback();

  /** Auto render image after changing any option if the corresponding member
   * variable is set. */
  void autoRenderCallback();

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
  bool eventFilter(QObject *object, QEvent *event);

  /** Is the rendering process in progress? */
  QMutex inProgressMutex;

  /** Communication with the raytracer library. */
  Raytracer::Api *api;

  /** Update zoom level label. */
  void updateZoomLevelLabel();

  /** Is the rendering process in progress? */
  QLabel *statusInProgressLabel;

  /** Time spent to render the last scene. */
  QLabel *statusRenderingTime;

  /** Auto render image after changing any option? */
  QCheckBox *autoRenderCheckBox;

  /** Carthesian coordinates label. */
  QLabel *statusEyeCarthesianLabel;

  /** Spherical coordinates label. */
  QLabel *statusEyeSphericalLabel;
};

#endif // _MAINWINDOW_MINE_
