#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
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
    void on_actionQuit_triggered();
    void horizontalResolutionChanged(int);
    void verticalResolutionChanged(int);
    void numberOfSamplesChanged(int);
    void pixelSizeChanged(double);
    void gammaCorrectionChanged(double);
    void ambientRadianceChanged(double);
    void updateRaytracerImage();

    void on_actionSave_PNG_Image_triggered();
    void on_actionAbout_triggered();
    void on_backgroundColorPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QLabel* raytracerWorkingLabel;

    Raytracer raytracer;
};

#endif // MAINWINDOW_H
