#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* ui initial values */
    raytracer.set_hres(ui->horizontalResolutionSpinBox->value());
    raytracer.set_vres(ui->verticalResolutionSpinBox->value());
    raytracer.set_number_of_samples(ui->numberOfSamplesSpinBox->value());
    raytracer.set_pixel_size(ui->pixelSizeDoubleSpinBox->value());
    raytracer.set_gamma_correction(ui->gammaCorrectionDoubleSpinBox->value());

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

void MainWindow::numberOfSamplesChanged(int samples) {
    raytracer.set_number_of_samples(samples);
    updateRaytracerImage();
}

void MainWindow::pixelSizeChanged(double size) {
    raytracer.set_pixel_size(size);
    updateRaytracerImage();
}

void MainWindow::gammaCorrectionChanged(double gamma) {
    raytracer.set_gamma_correction(gamma);
    updateRaytracerImage();
}

void MainWindow::updateRaytracerImage() {
    raytracer.render_scene();
    ui->raytracedImage->setPixmap(QPixmap(raytracer.image));
}
