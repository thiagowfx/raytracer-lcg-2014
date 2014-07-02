#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {

  /** Set up MainWindow */
  ui->setupUi(this);
  this->setFocus();
  // this->installEventFilter(this);

  std::cout << "teste" << std::endl;

  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), &api, SLOT(set_hres(int)));
  ui->horizontalResolutionSpinBox->setValue(api.get_hres());

  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(printCallback()));
  ui->verticalResolutionSpinBox->setValue(api.get_vres());
}


MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::printCallback() {
  std::cout << "callback" << std::endl;
  std::cout << api.get_hres() << std::endl;
}
