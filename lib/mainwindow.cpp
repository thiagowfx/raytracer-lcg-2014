#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  /** MainWindow */
  ui->setupUi(this);
  this->setFocus();
  this->installEventFilter(this);
  createStatusBar();

  /** ui initial values */
  raytracer.set_hres(ui->horizontalResolutionSpinBox->value());
  raytracer.set_vres(ui->verticalResolutionSpinBox->value());
  raytracer.set_number_of_samples(stoi(ui->numberOfSamplesComboBox->currentText().toStdString()));
  raytracer.set_max_depth(ui->maxDepthSpinBox->value());
  raytracer.set_pixel_size(ui->pixelSizeDoubleSpinBox->value());
  raytracer.set_camera_zoom(ui->zoomDoubleSpinBox->value());
  raytracer.set_gamma(ui->gammaCorrectionDoubleSpinBox->value());
  raytracer.set_view_distance(ui->viewPlaneDistanceDoubleSpinBox->value());
  raytracer.set_out_of_gamut(ui->outOfGamutCheckBox->isChecked());
  raytracer.set_background_color(ui->backgroundColorPushButton->palette().color(QPalette::Window));
  raytracer.set_tracer(ui->tracerComboBox->currentText());
  update_ambient_light();

  ui->autoRenderingCheckBox->setChecked(true);
  updateRaytracerImage();
}

void MainWindow::createStatusBar() {
  statusbarProgressLabel = new QLabel();
  statusbarCameraEyeLabel = new QLabel();
  statusbarCameraEyeCylindricalLabel = new QLabel();
  statusBar()->addPermanentWidget(statusbarProgressLabel);
  statusBar()->addWidget(statusbarCameraEyeLabel);
  statusBar()->addWidget(statusbarCameraEyeCylindricalLabel);
}

void MainWindow::updateStatusBar() {
  statusbarCameraEyeLabel->setText(raytracer.get_camera_eye_as_string());
  statusbarCameraEyeCylindricalLabel->setText(raytracer.get_camera_eye_cylindrical_as_string());
}

MainWindow::~MainWindow() {
  delete ui;
  delete statusbarCameraEyeLabel;
  delete statusbarCameraEyeCylindricalLabel;
  delete statusbarProgressLabel;
}

void MainWindow::horizontalResolutionChanged(int resolution) {
  raytracer.set_hres(resolution);
  ui->raytracedImage->adjustSize();
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::verticalResolutionChanged(int resolution) {
  raytracer.set_vres(resolution);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::numberOfSamplesChanged() {
  cout << stoi(ui->numberOfSamplesComboBox->currentText().toStdString()) << endl;
  raytracer.set_number_of_samples(stoi(ui->numberOfSamplesComboBox->currentText().toStdString()));
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::maxDepthChanged(int depth) {
  raytracer.set_max_depth(depth);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::pixelSizeChanged(double size) {
  raytracer.set_pixel_size(size);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::zoomChanged(double z) {
  raytracer.set_camera_zoom(z);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::gammaCorrectionChanged(double gamma) {
  raytracer.set_gamma(gamma);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::viewPlaneDistanceChanged(double d) {
  raytracer.set_view_distance(d);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::outOfGamutChanged() {
  raytracer.set_out_of_gamut(ui->outOfGamutCheckBox->isChecked());
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::tracerChanged(QString s) {
  raytracer.set_tracer(s);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::updateRaytracerImage() {
  if (!mutex.tryLock())
    return;

  statusbarProgressLabel->setText("Rendering...");
  updateStatusBar();
  QCoreApplication::processEvents();

  raytracer.render_scene();
  ui->raytracedImage->setPixmap(QPixmap(raytracer.image));

  statusbarProgressLabel->setText("Idle");
  QCoreApplication::processEvents();

  mutex.unlock();
}

void MainWindow::on_actionQuit_triggered() {
  QApplication::quit();
}

void MainWindow::on_actionSave_PNG_Image_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
                                                  this,
                                                  tr("Export Image"),
                                                  tr("."),
                                                  tr("Images (*.bmp *.gif *.png *.jpg *.jpeg)"));
  ui->raytracedImage->pixmap()->save(fileName);
}

void MainWindow::on_backgroundColorPushButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this);
  if (color.isValid()) {
    ui->backgroundColorPushButton->setPalette(QPalette(color));
    raytracer.set_background_color(color);
    if (ui->autoRenderingCheckBox->isChecked())
      updateRaytracerImage();
  }
}


void MainWindow::update_ambient_light() {
  Ambient* ambient_light;

  QString ambient_type = ui->ambientLightComboBox->currentText();
  if (ambient_type == "AmbientOccluder")
    ambient_light = new AmbientOccluder();
  else
    ambient_light = new Ambient();

  double radiance = ui->ambientRadianceDoubleSpinBox->value();
  ambient_light->scale_radiance(radiance);

  QColor color = ui->ambientColorPushButton->palette().color(QPalette::Window);
  if (color.isValid())
    ambient_light->set_color(color.redF(), color.greenF(), color.blueF());

  raytracer.set_ambient_light(ambient_light);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Left_pressed() {
  raytracer.camera_eye_relative_spherical(0.0, +M_PI/30.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Right_pressed() {
  raytracer.camera_eye_relative_spherical(0.0, -M_PI/30.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Up_pressed() {
  raytracer.camera_eye_relative_spherical(0.0, 0.0, -M_PI/30.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Down_pressed() {
  raytracer.camera_eye_relative_spherical(0.0, 0.0, +M_PI/30.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_PageUp_pressed() {
  raytracer.camera_eye_relative_spherical(-10.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_PageDown_pressed() {
  raytracer.camera_eye_relative_spherical(+10.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_W_pressed() {
  raytracer.camera_eye_relative(0.0, 5.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_S_pressed() {
  raytracer.camera_eye_relative(0.0, -5.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_A_pressed() {
  raytracer.camera_eye_relative(-5.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_D_pressed() {
  raytracer.camera_eye_relative(5.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_R_pressed() {
  raytracer.camera_eye_relative(0.0, 0.0, 5.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_F_pressed() {
  raytracer.camera_eye_relative(0.0, 0.0, -5.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    switch(keyEvent->key()){
    case Qt::Key_Left:
      on_Key_Left_pressed();
      break;
    case Qt::Key_Right:
      on_Key_Right_pressed();
      break;
    case Qt::Key_Up:
      on_Key_Up_pressed();
      break;
    case Qt::Key_Down:
      on_Key_Down_pressed();
      break;
    case Qt::Key_PageUp:
      on_Key_PageUp_pressed();
      break;
    case Qt::Key_PageDown:
      on_Key_PageDown_pressed();
      break;
    case Qt::Key_W:
      on_Key_W_pressed();
      break;
    case Qt::Key_S:
      on_Key_S_pressed();
      break;
    case Qt::Key_A:
      on_Key_A_pressed();
      break;
    case Qt::Key_D:
      on_Key_D_pressed();
      break;
    case Qt::Key_R:
      on_Key_R_pressed();
      break;
    case Qt::Key_F:
      on_Key_F_pressed();
      break;
    }
  }
  return false;
}

void MainWindow::on_actionAbout_Qt_triggered() {
  QMessageBox::aboutQt(this);
}

void MainWindow::on_actionReset_camera_triggered() {
  raytracer.set_up_camera();
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_ambientColorPushButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  if (color.isValid()) {
    ui->ambientColorPushButton->setPalette(QPalette(color));
    update_ambient_light();
  }
}
