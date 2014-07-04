#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  api(new Raytracer::Api) {

  ui->setupUi(this);
  this->setFocus();
  // this->installEventFilter(this);

  ui->horizontalResolutionSpinBox->setMinimum(1);
  ui->horizontalResolutionSpinBox->setSingleStep(10);
  api->set_hres(400);
  ui->horizontalResolutionSpinBox->setValue(api->get_hres());
  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_hres(int)));

  ui->verticalResolutionSpinBox->setMinimum(1);
  ui->verticalResolutionSpinBox->setSingleStep(10);
  api->set_vres(400);
  ui->verticalResolutionSpinBox->setValue(api->get_vres());
  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_vres(int)));

  ui->pixelSizeDoubleSpinBox->setMinimum(0.01);
  ui->pixelSizeDoubleSpinBox->setSingleStep(0.1);
  api->set_pixel_size(1.0);
  ui->pixelSizeDoubleSpinBox->setValue(api->get_pixel_size());
  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_pixel_size(int)));

  ui->gammaLevelDoubleSpinBox->setMinimum(0.01);
  ui->gammaLevelDoubleSpinBox->setSingleStep(0.1);
  api->set_gamma(1.0);
  ui->gammaLevelDoubleSpinBox->setValue(api->get_gamma());
  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_gamma(double)));

  api->set_out_of_gamut(true);
  ui->outOfGamutCheckBox->setChecked(api->get_out_of_gamut());
  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), api, SLOT(set_out_of_gamut(bool)));

  api->set_max_depth(1);
  ui->maxDepthSpinBox->setValue(api->get_max_depth());
  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_max_depth(int)));

  ui->numberOfSamplesSpinBox->setMinimum(1);
  ui->samplerTypeComboBox->setModel(api->get_sampler_type_model());
  api->set_sampler(tr("Regular"), 4);
  ui->numberOfSamplesSpinBox->setValue(api->get_number_of_samples());
  ui->samplerTypeComboBox->setCurrentText(tr(api->get_sampler_type()));
  QObject::connect(ui->numberOfSamplesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(samplerCallback()));
  QObject::connect(ui->samplerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(samplerCallback()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::printCallback() {
  std::cout << "callback" << std::endl;
  qDebug("debug\n");
}

void MainWindow::samplerCallback() {
  api->set_sampler(ui->samplerTypeComboBox->currentText(), ui->numberOfSamplesSpinBox->value());
}

void MainWindow::on_actionQuit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QMessageBox::aboutQt(this);
}
