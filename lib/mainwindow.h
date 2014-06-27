#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMutex>
#include <QPalette>
#include <QString>
#include "Raytracer.h"

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
  void horizontalResolutionChanged(int);
  void verticalResolutionChanged(int);
  void numberOfSamplesChanged();
  void maxDepthChanged(int);
  void pixelSizeChanged(double);
  void zoomChanged(double);
  void gammaCorrectionChanged(double);
  void viewPlaneDistanceChanged(double);
  void outOfGamutChanged();
  void tracerChanged(QString);
  void updateRaytracerImage();

  void on_backgroundColorPushButton_clicked();
  void on_ambientColorPushButton_clicked();

  /** Actions */
  void on_actionQuit_triggered();
  void on_actionSave_PNG_Image_triggered();
  void on_actionAbout_triggered();
  void on_actionAbout_Qt_triggered();
  void on_actionReset_camera_triggered();

  void update_ambient_light();

private:
  /* Keys */
  bool eventFilter(QObject *object, QEvent *event);
  void on_Key_Left_pressed();
  void on_Key_Right_pressed();
  void on_Key_Up_pressed();
  void on_Key_Down_pressed();
  void on_Key_PageUp_pressed();
  void on_Key_PageDown_pressed();
  void on_Key_W_pressed();
  void on_Key_S_pressed();
  void on_Key_A_pressed();
  void on_Key_D_pressed();
  void on_Key_R_pressed();
  void on_Key_F_pressed();

  void createStatusBar();
  void updateStatusBar();

  Ui::MainWindow *ui;
  Raytracer raytracer;
  QMutex mutex; /* raytracingInProgress? */
  QLabel *statusbarCameraEyeLabel;
  QLabel *statusbarCameraEyeCylindricalLabel;
  QLabel *statusbarProgressLabel;
};

#endif // MAINWINDOW_H
