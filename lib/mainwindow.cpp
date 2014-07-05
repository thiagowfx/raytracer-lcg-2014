#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow()),
  api(new Raytracer::Api()),
  statusInProgressLabel(new QLabel()),
  autoRenderCheckBox(new QCheckBox(tr("Auto-render?"), this->statusBar())),
  statusEyeCarthesianLabel(new QLabel()),
  statusEyeSphericalLabel(new QLabel()) {

  ui->setupUi(this);
  this->setFocus();
  this->installEventFilter(this);

  statusBar()->addPermanentWidget(statusInProgressLabel);
  statusBar()->addWidget(autoRenderCheckBox);
  statusBar()->addWidget(statusEyeCarthesianLabel);
  statusBar()->addWidget(statusEyeSphericalLabel);

  ui->horizontalResolutionSpinBox->setMinimum(1);
  ui->horizontalResolutionSpinBox->setSingleStep(10);
  api->set_hres(400);
  ui->horizontalResolutionSpinBox->setValue(api->get_hres());
  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_hres(int)));
  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(autoRenderCallback()));

  ui->verticalResolutionSpinBox->setMinimum(1);
  ui->verticalResolutionSpinBox->setSingleStep(10);
  api->set_vres(400);
  ui->verticalResolutionSpinBox->setValue(api->get_vres());
  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_vres(int)));
  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(autoRenderCallback()));

  ui->pixelSizeDoubleSpinBox->setMinimum(0.01);
  ui->pixelSizeDoubleSpinBox->setSingleStep(0.1);
  api->set_pixel_size(1.0);
  ui->pixelSizeDoubleSpinBox->setValue(api->get_pixel_size());
  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_pixel_size(double)));
  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(autoRenderCallback()));

  ui->gammaLevelDoubleSpinBox->setMinimum(0.01);
  ui->gammaLevelDoubleSpinBox->setSingleStep(0.1);
  api->set_gamma(1.0);
  ui->gammaLevelDoubleSpinBox->setValue(api->get_gamma());
  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_gamma(double)));
  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(autoRenderCallback()));

  api->set_out_of_gamut(true);
  ui->outOfGamutCheckBox->setChecked(api->get_out_of_gamut());
  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), api, SLOT(set_out_of_gamut(bool)));
  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), this, SLOT(autoRenderCallback()));

  api->set_max_depth(1);
  ui->maxDepthSpinBox->setValue(api->get_max_depth());
  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_max_depth(int)));
  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(autoRenderCallback()));


  ui->numberOfSamplesSpinBox->setMinimum(1);
  ui->samplerTypeComboBox->setModel(api->get_sampler_type_model());
  api->set_sampler(tr("Regular"), 4);
  ui->numberOfSamplesSpinBox->setValue(api->get_number_of_samples());
  ui->samplerTypeComboBox->setCurrentText(tr(api->get_sampler_type()));
  QObject::connect(ui->numberOfSamplesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(samplerCallback()));
  QObject::connect(ui->numberOfSamplesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(autoRenderCallback()));
  QObject::connect(ui->samplerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(samplerCallback()));
  QObject::connect(ui->samplerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(autoRenderCallback()));

  ui->tracerTypeComboBox->setModel(api->get_tracer_type_model());
  api->set_tracer_type(tr("MultipleObjects"));
  ui->tracerTypeComboBox->setCurrentText(api->get_tracer_type());
  QObject::connect(ui->tracerTypeComboBox, SIGNAL(currentIndexChanged(QString)), api, SLOT(set_tracer_type(QString)));
  QObject::connect(ui->tracerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(autoRenderCallback()));

  api->set_background_color(QColor(Qt::white));
  ui->backgroundColorPushButton->setPalette(api->get_background_color());
  QObject::connect(ui->backgroundColorPushButton, SIGNAL(clicked()), this, SLOT(backgroundColorCallback()));
  QObject::connect(ui->backgroundColorPushButton, SIGNAL(clicked()), this, SLOT(autoRenderCallback()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete api;
  delete statusInProgressLabel;
  delete statusEyeCarthesianLabel;
  delete statusEyeSphericalLabel;
  delete autoRenderCheckBox;
}

void MainWindow::samplerCallback() {
  api->set_sampler(ui->samplerTypeComboBox->currentText(), ui->numberOfSamplesSpinBox->value());
}

void MainWindow::backgroundColorCallback() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  if (color.isValid()) {
    ui->backgroundColorPushButton->setPalette(QPalette(color));
    api->set_background_color(color);
  }
}

void MainWindow::autoRenderCallback() {
  if (autoRenderCheckBox->isChecked())
    on_actionRender_scene_triggered();
}

void MainWindow::on_actionQuit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionRender_scene_triggered() {
    if (!inProgressMutex.tryLock())
      return;

    /* Statusbar. */
    statusInProgressLabel->setText("Rendering...");
    statusEyeCarthesianLabel->setText(tr(api->get_eye_carthesian_coordinates()));
    statusEyeSphericalLabel->setText(tr(api->get_eye_spherical_coordinates()));

    QCoreApplication::processEvents();

    /* Rendering. */
    api->render_scene();
    ui->renderedImage->setPixmap(QPixmap(api->get_rendered_image()));

    statusInProgressLabel->setText("Idle.");

    QCoreApplication::processEvents();

    inProgressMutex.unlock();
}

void MainWindow::on_actionExport_Image_triggered() {
  QString file = QFileDialog::getSaveFileName(this,
                                              tr("Export Image"),
                                              tr("."),
                                              tr("Image Files (*.bmp *.gif *.png *.jpg *.jpeg)"));
  ui->renderedImage->pixmap()->save(file);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
  double drotation = M_PI / 30.0;
  double dradius = 10.0;

  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    switch(keyEvent->key()){
    case Qt::Key_Left:
      api->set_eye_spherical_relatively(0.0, -drotation, 0.0);
      break;
    case Qt::Key_Right:
      api->set_eye_spherical_relatively(0.0, +drotation, 0.0);
      break;
    case Qt::Key_Up:
      api->set_eye_spherical_relatively(0.0, 0.0, -drotation);
      break;
    case Qt::Key_Down:
      api->set_eye_spherical_relatively(0.0, 0.0, +drotation);
      break;
    case Qt::Key_PageUp:
      api->set_eye_spherical_relatively(-dradius, 0.0, 0.0);
      break;
    case Qt::Key_PageDown:
      api->set_eye_spherical_relatively(+dradius, 0.0, 0.0);
      break;
    default:
      return false;
    }
    on_actionRender_scene_triggered();
  }
  return false;
}
