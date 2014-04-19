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
    void numberOfSamplesChanged(int);
    void pixelSizeChanged(double);
    void gammaCorrectionChanged(double);
    void outOfGamutChanged();
    void ambientRadianceChanged(double);
    void updateRaytracerImage();
    void tracerChanged(QString);

    void on_backgroundColorPushButton_clicked();
    void on_ambientColorPushButton_clicked();

    /** Actions */
    void on_actionQuit_triggered();
    void on_actionSave_PNG_Image_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();

private:
    void on_Key_Left_pressed();
    void on_Key_Right_pressed();
    void on_Key_Up_pressed();
    void on_Key_Down_pressed();
    void on_Key_W_pressed();
    void on_Key_S_pressed();

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *object, QEvent *event);

    Raytracer raytracer;
    bool raytracingInProgress;
    QLabel *statusbarCameraEyeLabel;
    QLabel *statusbarCameraEyeCylindricalLabel;
    QLabel *statusbarProgressLabel;
};

#endif // MAINWINDOW_H
