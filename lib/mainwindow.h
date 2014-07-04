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

  /******************* Actions ******************/
  void on_actionQuit_triggered();
  void on_actionAbout_Qt_triggered();
  void on_actionRender_scene_triggered();
  void on_actionExport_Image_triggered();

private:
  Ui::MainWindow *ui;
  Raytracer::Api *api;
};

#endif // MAINWINDOW_H
