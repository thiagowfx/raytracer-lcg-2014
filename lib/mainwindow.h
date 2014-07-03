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
  void printCallback();

private:
  Ui::MainWindow *ui;
  Raytracer::Api *api;
};

#endif // MAINWINDOW_H
