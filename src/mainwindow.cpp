#include "mainwindow.hpp"
#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"
#include "menus/filemenu.hpp"
#include "menus/imagemenu.hpp"
#include "statusbar/mainstatusbar.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), mdi_area_(new QMdiArea()) {
  createMenus();
  createStatusBar();

  mdi_area_->setTabsClosable(true);
  mdi_area_->setTabsMovable(true);

  setCentralWidget(mdi_area_);

  connect(mdi_area_, &QMdiArea::subWindowActivated, this,
          [this](const QMdiSubWindow *w) {
            emit activeImageChanged(activeImage());
          });
}

void MainWindow::open() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  if (!file_path.isEmpty()) {
    addImageDisplayArea(new ProImage(file_path));
  }
}

void MainWindow::save() {
  ProImage *active_image = activeImage();

  // TODO: Remove code duplication
  if (!active_image) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  if (active_image->save()) {
    statusBar()->showMessage(
        QString("Saved image on %1").arg(active_image->filePath()));
  } else {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  }
}

void MainWindow::saveAs() {
  ProImage *image = activeImage();

  if (!image) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  // TODO: Enforce save with image extension
  QString file_path = QFileDialog::getSaveFileName(
      this, tr("Save Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  if (!file_path.isEmpty() && !image->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  } else {
    statusBar()->showMessage(QString("Saved image on %1").arg(file_path));
    image->setFilePath(file_path);
  }
}

void MainWindow::addImageDisplayArea(const ProImage *image) {
  ImageDisplayArea *display_area = new ImageDisplayArea();

  display_area->setImage(image);
  mdi_area_->addSubWindow(display_area);
  display_area->show();

  connect(display_area, &ImageDisplayArea::pixelInformation,
          main_status_bar_->pixelInfoWidget(),
          &PixelInformationWidget::onPixelInformationReceived);
}

void MainWindow::createMenus() {
  file_menu_ = new FileMenu();
  image_menu_ = new ImageMenu();
  menuBar()->addMenu(file_menu_);
  menuBar()->addMenu(image_menu_);

  // Connections
  connect(file_menu_->openAct(), &QAction::triggered, this, &MainWindow::open);
  connect(file_menu_->saveAct(), &QAction::triggered, this, &MainWindow::save);
  connect(file_menu_->saveAsAct(), &QAction::triggered, this,
          &MainWindow::saveAs);
  connect(file_menu_->quitAct(), &QAction::triggered, qApp,
          &QApplication::quit);
}

void MainWindow::createStatusBar() {
  main_status_bar_ = new MainStatusBar();
  setStatusBar(main_status_bar_);
}

ProImage *MainWindow::activeImage() const {
  ProImage *image = nullptr;

  QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow();
  if (active_subwindow) {
    ImageDisplayArea *display_area =
        dynamic_cast<ImageDisplayArea *>(active_subwindow->widget());
    if (display_area) {
      image = const_cast<ProImage *>(display_area->image());
    }
  }

  return image;
}
