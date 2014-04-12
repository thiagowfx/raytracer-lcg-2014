#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void updateRaytracerImage();
    
private slots:
    void on_actionQuit_triggered();
    void horizontalResolutionChanged(int);
    void verticalResolutionChanged(int);

private:
    Ui::MainWindow *ui;
    Raytracer raytracer;
};

#endif // MAINWINDOW_H
