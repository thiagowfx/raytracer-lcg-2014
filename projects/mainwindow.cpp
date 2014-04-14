#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* ui initial values */
    raytracerWorkingLabel = new QLabel();
    statusBar()->addWidget(raytracerWorkingLabel);

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
    delete raytracerWorkingLabel;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSave_PNG_Image_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Export image"),
                tr("."),
                tr("Images (*.png *.jpg *.jpeg)"));
    ui->raytracedImage->pixmap()->save(fileName);
}

void MainWindow::horizontalResolutionChanged(int resolution) {
    raytracer.set_hres(resolution);
    if (ui->autoRenderingCheckBox->isChecked())
        updateRaytracerImage();
}

void MainWindow::verticalResolutionChanged(int resolution) {
    raytracer.set_vres(resolution);
    if (ui->autoRenderingCheckBox->isChecked())
        updateRaytracerImage();
}

void MainWindow::numberOfSamplesChanged(int samples) {
    raytracer.set_number_of_samples(samples);
    if (ui->autoRenderingCheckBox->isChecked())
        updateRaytracerImage();
}

void MainWindow::pixelSizeChanged(double size) {
    raytracer.set_pixel_size(size);
    if (ui->autoRenderingCheckBox->isChecked())
        updateRaytracerImage();
}

void MainWindow::gammaCorrectionChanged(double gamma) {
    raytracer.set_gamma_correction(gamma);
    if (ui->autoRenderingCheckBox->isChecked())
        updateRaytracerImage();
}

void MainWindow::updateRaytracerImage() {
    qDebug() << "updateRaytracerImage()";
    raytracerWorkingLabel->setText(tr("Rendering scene..."));
    raytracer.render_scene();
    ui->raytracedImage->setPixmap(QPixmap(raytracer.image));
    raytracerWorkingLabel->setText(tr("Idle"));
}
