#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "RaytracerApi.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void samplerCallback();
  void backgroundColorCallback();
  void ambientLightColorCallback();
  void ambientLightCallback();
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

private:
  Ui::MainWindow *ui;

  /** Bind keys to events. */
  bool eventFilter(QObject *object, QEvent *event);

  /** Is the rendering process in progress? */
  QMutex inProgressMutex;

  /** Communication with the raytracer library. */
  Raytracer::Api *api;

  /** Is the rendering process in progress? */
  QLabel *statusInProgressLabel;

  /** Auto render image after changing any option? */
  QCheckBox *autoRenderCheckBox;

  /** Carthesian coordinates label. */
  QLabel *statusEyeCarthesianLabel;

  /** Spherical coordinates label. */
  QLabel *statusEyeSphericalLabel;
};

#endif // MAINWINDOW_H
