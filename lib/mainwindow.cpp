#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  api(new Raytracer::Api) {

  /** Set up */
  ui->setupUi(this);
  this->setFocus();
  // this->installEventFilter(this);

  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_hres(int)));
  ui->horizontalResolutionSpinBox->setValue(api->get_hres());

  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_vres(int)));
  ui->verticalResolutionSpinBox->setValue(api->get_vres());

  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_pixel_size(int)));
  ui->pixelSizeDoubleSpinBox->setValue(api->get_pixel_size());

  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_gamma(double)));
  ui->gammaLevelDoubleSpinBox->setValue(api->get_gamma());

  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), api, SLOT(set_out_of_gamut(bool)));
  ui->outOfGamutCheckBox->setChecked(api->get_out_of_gamut());

  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_max_depth(int)));
  ui->maxDepthSpinBox->setValue(api->get_max_depth());
}


MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::printCallback() {
  std::cout << "callback" << std::endl;
}
