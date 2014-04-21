#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  /** MainWindow */
  ui->setupUi(this);
  this->setWindowTitle(tr("Raytracer"));
  this->setFocus();
  this->installEventFilter(this);

  createStatusBar();

  /** ui initial values */
  raytracingInProgress = false;
  raytracer.set_hres(ui->horizontalResolutionSpinBox->value());
  raytracer.set_vres(ui->verticalResolutionSpinBox->value());
  raytracer.set_number_of_samples(ui->numberOfSamplesSpinBox->value());
  raytracer.set_pixel_size(ui->pixelSizeDoubleSpinBox->value());
  raytracer.set_camera_zoom(ui->zoomDoubleSpinBox->value());
  raytracer.set_gamma_correction(ui->gammaCorrectionDoubleSpinBox->value());
  raytracer.set_view_distance(ui->viewPlaneDistanceDoubleSpinBox->value());
  raytracer.set_show_out_of_gamut(ui->outOfGamutCheckBox->isChecked());
  raytracer.set_background_color(ui->backgroundColorPushButton->palette().color(QPalette::Window));
  raytracer.set_ambient_light_color(ui->ambientColorPushButton->palette().color(QPalette::Window));
  raytracer.set_ambient_radiance(ui->ambientRadianceDoubleSpinBox->value());
  raytracer.set_tracer(ui->tracerComboBox->currentText());

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

void MainWindow::zoomChanged(double z) {
  raytracer.set_camera_zoom(z);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::gammaCorrectionChanged(double gamma) {
  raytracer.set_gamma_correction(gamma);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::viewPlaneDistanceChanged(double d) {
  raytracer.set_view_distance(d);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::outOfGamutChanged() {
  raytracer.set_show_out_of_gamut(ui->outOfGamutCheckBox->isChecked());
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::ambientRadianceChanged(double r) {
  raytracer.set_ambient_radiance(r);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::updateRaytracerImage() {
  if (raytracingInProgress)
    return;

  raytracingInProgress = true;
  statusbarCameraEyeLabel->setText(raytracer.get_camera_eye_as_string());
  statusbarCameraEyeCylindricalLabel->setText(raytracer.get_camera_eye_cylindrical_as_string());
  statusbarProgressLabel->setText("Rendering...");
  QApplication::instance()->processEvents();

  raytracer.render_scene();
  ui->raytracedImage->setPixmap(QPixmap(raytracer.image));

  statusbarProgressLabel->setText("Idle");
  raytracingInProgress = false;
}

void MainWindow::tracerChanged(QString s) {
  raytracer.set_tracer(s);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_actionQuit_triggered() {
  QApplication::quit();
}

void MainWindow::on_actionSave_PNG_Image_triggered() {
  /** http://qt-project.org/doc/qt-5/qpixmap.html#reading-and-writing-image-files */
  QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Export Image"),
        tr("."),
        tr("Images (*.bmp *.gif *.png *.jpg *.jpeg)"));
  ui->raytracedImage->pixmap()->save(fileName);
}

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::about(this,
                     tr("About"),
                     tr("A simple raytracer"));
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


void MainWindow::on_ambientColorPushButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  if (color.isValid()) {
    ui->ambientColorPushButton->setPalette(QPalette(color));
    raytracer.set_ambient_light_color(color);
    if (ui->autoRenderingCheckBox->isChecked())
      updateRaytracerImage();
  }
}

void MainWindow::on_Key_Left_pressed() {
  qDebug() << "INFO: left arrow pressed";
  raytracer.move_camera_eye_relative_cylindrical(0.0, M_PI/60.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Right_pressed() {
  qDebug() << "INFO: right arrow pressed";
  raytracer.move_camera_eye_relative_cylindrical(0.0, -M_PI/60.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Up_pressed() {
  qDebug() << "INFO: up arrow pressed";
  raytracer.move_camera_eye_relative_cylindrical(-5.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_Down_pressed() {
  qDebug() << "INFO: down arrow pressed";
  raytracer.move_camera_eye_relative_cylindrical(5.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_PageUp_pressed() {
  qDebug() << "INFO: Page Up key pressed";
  raytracer.move_camera_eye_relative_cylindrical(0.0, 0.0, 5.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_PageDown_pressed() {
  qDebug() << "INFO: Page Down key pressed";
  raytracer.move_camera_eye_relative_cylindrical(0.0, 0.0, -5.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_W_pressed() {
  qDebug() << "INFO: W key pressed";
  raytracer.move_camera_eye_relative(0.0, 5.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_S_pressed() {
  qDebug() << "INFO: S key pressed";
  raytracer.move_camera_eye_relative(0.0, -5.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_A_pressed() {
  qDebug() << "INFO: A key pressed";
  raytracer.move_camera_eye_relative(-5.0, 0.0, 0.0);
  if (ui->autoRenderingCheckBox->isChecked())
    updateRaytracerImage();
}

void MainWindow::on_Key_D_pressed() {
  qDebug() << "INFO: D key pressed";
  raytracer.move_camera_eye_relative(5.0, 0.0, 0.0);
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
