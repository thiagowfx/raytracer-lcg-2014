#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui initial values
    raytracer.set_hres(ui->horizontalResolutionSpinBox->value());
    raytracer.set_vres(ui->verticalResolutionSpinBox->value());

    updateRaytracerImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::horizontalResolutionChanged(int resolution) {
    raytracer.set_hres(resolution);
    updateRaytracerImage();
}

void MainWindow::verticalResolutionChanged(int resolution) {
    raytracer.set_vres(resolution);
    updateRaytracerImage();
}

void MainWindow::updateRaytracerImage() {
    raytracer.render_scene();
    ui->raytracedImage->setPixmap(QPixmap(raytracer.image));
}
