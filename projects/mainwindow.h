#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>
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
    void numberOfSamplesChanged(int);
    void pixelSizeChanged(double);
    void gammaCorrectionChanged(double);
    void ambientRadianceChanged(double);
    void updateRaytracerImage();

    void on_actionQuit_triggered();
    void on_actionSave_PNG_Image_triggered();
    void on_actionAbout_triggered();
    void on_backgroundColorPushButton_clicked();

private:
    void on_leftArrow_pressed();
    void on_rightArrow_pressed();
    void on_upArrow_pressed();
    void on_downArrow_pressed();

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *object, QEvent *event);

    Raytracer raytracer;
    bool raytracingInProgress;
    QLabel *statusbarCameraEyeLabel;
    QLabel *statusbarCameraEyeSphericalLabel;
    QLabel *statusbarProgressLabel;
};

#endif // MAINWINDOW_H
