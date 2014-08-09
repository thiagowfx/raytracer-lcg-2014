#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow()),
  api(new Raytracer::Api()),
  status_in_progress_label(new QLabel()),
  status_rendering_time(new QLabel()),
  auto_render_checkbox(new QCheckBox(tr("Auto-render?"), this->statusBar())) {

  auto_render_checkbox->setChecked(true);

  ui->setupUi(this);
  this->setFocus();
  this->installEventFilter(this);
  ui->renderedImage->installEventFilter(this);

  update_zoom_level_label();
  update_eye_carthesian_label();
  update_eye_spherical_label();
  statusBar()->addPermanentWidget(status_in_progress_label);
  statusBar()->addPermanentWidget(status_rendering_time);
  statusBar()->addWidget(auto_render_checkbox);

  ui->horizontalResolutionSpinBox->setMinimum(1);
  ui->horizontalResolutionSpinBox->setSingleStep(10);
  api->set_hres(400);
  ui->horizontalResolutionSpinBox->setValue(api->get_hres());
  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_hres(int)));
  QObject::connect(ui->horizontalResolutionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(auto_render_callback()));

  ui->verticalResolutionSpinBox->setMinimum(1);
  ui->verticalResolutionSpinBox->setSingleStep(10);
  api->set_vres(400);
  ui->verticalResolutionSpinBox->setValue(api->get_vres());
  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_vres(int)));
  QObject::connect(ui->verticalResolutionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(auto_render_callback()));

  ui->pixelSizeDoubleSpinBox->setMinimum(0.01);
  ui->pixelSizeDoubleSpinBox->setSingleStep(0.1);
  api->set_pixel_size(1.0);
  ui->pixelSizeDoubleSpinBox->setValue(api->get_pixel_size());
  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_pixel_size(double)));
  QObject::connect(ui->pixelSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(auto_render_callback()));

  ui->gammaLevelDoubleSpinBox->setMinimum(0.01);
  ui->gammaLevelDoubleSpinBox->setSingleStep(0.1);
  api->set_gamma(1.0);
  ui->gammaLevelDoubleSpinBox->setValue(api->get_gamma());
  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_gamma(double)));
  QObject::connect(ui->gammaLevelDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(auto_render_callback()));

  api->set_out_of_gamut(true);
  ui->outOfGamutCheckBox->setChecked(api->get_out_of_gamut());
  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), api, SLOT(set_out_of_gamut(bool)));
  QObject::connect(ui->outOfGamutCheckBox, SIGNAL(toggled(bool)), this, SLOT(auto_render_callback()));

  api->set_max_depth(1);
  ui->maxDepthSpinBox->setValue(api->get_max_depth());
  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), api, SLOT(set_max_depth(int)));
  QObject::connect(ui->maxDepthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(auto_render_callback()));


  ui->numberOfSamplesSpinBox->setMinimum(1);
  ui->samplerTypeComboBox->setModel(api->get_sampler_type_model());
  api->set_sampler(tr("MultiJittered"), 3);
  ui->numberOfSamplesSpinBox->setValue(api->get_number_of_samples());
  ui->samplerTypeComboBox->setCurrentText(tr(api->get_sampler_type()));
  QObject::connect(ui->numberOfSamplesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sampler_callback()));
  QObject::connect(ui->numberOfSamplesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(auto_render_callback()));
  QObject::connect(ui->samplerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(sampler_callback()));
  QObject::connect(ui->samplerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(auto_render_callback()));

  ui->tracerTypeComboBox->setModel(api->get_tracer_type_model());
  api->set_tracer_type(tr("Whitted"));
  ui->tracerTypeComboBox->setCurrentText(api->get_tracer_type());
  QObject::connect(ui->tracerTypeComboBox, SIGNAL(currentIndexChanged(QString)), api, SLOT(set_tracer_type(QString)));
  QObject::connect(ui->tracerTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(auto_render_callback()));

  api->set_background_color(QColor(Qt::white));
  ui->backgroundColorPushButton->setPalette(api->get_background_color());
  QObject::connect(ui->backgroundColorPushButton, SIGNAL(clicked()), this, SLOT(background_color_callback()));
  QObject::connect(ui->backgroundColorPushButton, SIGNAL(clicked()), this, SLOT(auto_render_callback()));

  ui->ambientLightRadianceDoubleSpinBox->setSingleStep(0.1);
  ui->ambientLightTypeComboBox->setModel(api->get_ambient_light_type_model());
  api->set_ambient_light("Ambient", QColor(Qt::white), 1.0);
  ui->ambientLightColorPushButton->setPalette(api->get_ambient_light_color());
  ui->ambientLightRadianceDoubleSpinBox->setValue(api->get_ambient_light_radiance());
  ui->ambientLightTypeComboBox->setCurrentText(api->get_ambient_light_type());
  QObject::connect(ui->ambientLightColorPushButton, SIGNAL(clicked()), this, SLOT(ambient_light_color_callback()));
  QObject::connect(ui->ambientLightColorPushButton, SIGNAL(clicked()), this, SLOT(auto_render_callback()));
  QObject::connect(ui->ambientLightRadianceDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambient_light_callback()));
  QObject::connect(ui->ambientLightRadianceDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(auto_render_callback()));
  QObject::connect(ui->ambientLightTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(ambient_light_callback()));
  QObject::connect(ui->ambientLightTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(auto_render_callback()));

  ui->cameraDistanceDoubleSpinBox->setSingleStep(5.0);
  ui->cameraDistanceDoubleSpinBox->setMaximum(1000.0);
  api->set_camera_distance(100.0);
  ui->cameraDistanceDoubleSpinBox->setValue(api->get_camera_distance());
  QObject::connect(ui->cameraDistanceDoubleSpinBox, SIGNAL(valueChanged(double)), api, SLOT(set_camera_distance(double)));
  QObject::connect(ui->cameraDistanceDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(auto_render_callback()));

  auto_render_checkbox->setChecked(true);
  auto_render_callback();
}

MainWindow::~MainWindow() {
  delete ui;
  delete api;
  delete status_in_progress_label;
  delete status_rendering_time;
  delete auto_render_checkbox;
}

void MainWindow::sampler_callback() {
  api->set_sampler(ui->samplerTypeComboBox->currentText(), ui->numberOfSamplesSpinBox->value());
}

void MainWindow::background_color_callback() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  if (color.isValid()) {
    ui->backgroundColorPushButton->setPalette(QPalette(color));
    api->set_background_color(color);
  }
}

void MainWindow::ambient_light_color_callback() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  if (color.isValid()) {
    ui->ambientLightColorPushButton->setPalette(QPalette(color));
    ambient_light_callback();
  }
}

void MainWindow::ambient_light_callback() {
  api->set_ambient_light(ui->ambientLightTypeComboBox->currentText(),
                         ui->ambientLightColorPushButton->palette().color(QPalette::Button),
                         ui->ambientLightRadianceDoubleSpinBox->value());
}

void MainWindow::auto_render_callback() {
  if (auto_render_checkbox->isChecked())
    on_actionRender_scene_triggered();
}

void MainWindow::on_actionQuit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionRender_scene_triggered() {
    if (!in_progress_mutex.tryLock())
      return;

    /* Statusbar. */
    status_in_progress_label->setText("Rendering...");
    update_eye_carthesian_label();
    update_eye_spherical_label();

    QCoreApplication::processEvents();

    /* Rendering. */
    unsigned renderingTime = api->render_scene();
    status_rendering_time->setText("Rendering time: " + QString::number(renderingTime) + " ms");
    ui->renderedImage->setPixmap(QPixmap(api->get_rendered_image()));

    status_in_progress_label->setText("Idle.");

    QCoreApplication::processEvents();

    in_progress_mutex.unlock();
}

void MainWindow::on_actionExport_Image_triggered() {
  QString file = QFileDialog::getSaveFileName(this,
                                              tr("Export Image"),
                                              tr("."),
                                              tr("Image Files (*.bmp *.gif *.png *.jpg *.jpeg)"));
  ui->renderedImage->pixmap()->save(file);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
  const double ROTATION_VARIATION = M_PI / 55.0;
  const double RADIUS_VARIATION = 7.0;
  const double ZOOM_FRICTION = 1000.0;
  bool shouldRenderImage = false;

  /* renderedImage widget. */
  if (object == ui->renderedImage) {
    if (event->type() == QEvent::Wheel) {
      cout << "DEBUG: mouse wheel on rendered image" <<  endl;
      shouldRenderImage = true;
      QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

      const int delta = wheelEvent->delta();
      if (delta > 0) {
        api->zoom_increase(1.0 + (double(delta) / ZOOM_FRICTION));
      }
      else {
        api->zoom_decrease(1.0 - (double(delta) / ZOOM_FRICTION));
      }
      update_zoom_level_label();
    }
  }

  else if (event->type() == QEvent::KeyPress) {
    shouldRenderImage = true;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    cout << "DEBUG: key press" << endl;

    switch(keyEvent->key()){
    case Qt::Key_Escape:
      this->setFocus();
      break;
    case Qt::Key_Left:
      api->set_eye_spherical_relatively(0.0, +ROTATION_VARIATION, 0.0);
      break;
    case Qt::Key_Right:
      api->set_eye_spherical_relatively(0.0, -ROTATION_VARIATION, 0.0);
      break;
    case Qt::Key_Up:
      api->set_eye_spherical_relatively(0.0, 0.0, -ROTATION_VARIATION);
      break;
    case Qt::Key_Down:
      api->set_eye_spherical_relatively(0.0, 0.0, +ROTATION_VARIATION);
      break;
    case Qt::Key_PageUp:
      api->set_eye_spherical_relatively(-RADIUS_VARIATION, 0.0, 0.0);
      break;
    case Qt::Key_PageDown:
      api->set_eye_spherical_relatively(+RADIUS_VARIATION, 0.0, 0.0);
      break;
    }
  }

  if (shouldRenderImage) {
    auto_render_callback();
    return true;
  }

  return false;
}

void MainWindow::update_zoom_level_label() {
  ui->zoomLevelLabel->setText(QString::number(api->zoom_get(), 'g', 2) + " x");
}

void MainWindow::update_eye_carthesian_label() {
  ui->eyeCarthesianLabel->setText(api->get_eye_carthesian_coordinates());
}

void MainWindow::update_eye_spherical_label() {
  ui->eyeSphericalLabel->setText(api->get_eye_spherical_coordinates());
}

void MainWindow::on_actionZoom_In_triggered() {
  api->zoom_increase(1.05);
  auto_render_callback();
  update_zoom_level_label();
}

void MainWindow::on_actionZoom_Out_triggered() {
  api->zoom_decrease(1.05);
  auto_render_callback();
  update_zoom_level_label();
}

void MainWindow::on_actionZoom_Reset_triggered() {
  api->zoom_set(1.0);
  auto_render_callback();
  update_zoom_level_label();
}
