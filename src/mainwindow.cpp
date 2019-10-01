#include "mainwindow.hpp"
#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"
#include "manager/imagemanager.hpp"
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
            active_image_ = activeImage();
            emit activeImageChanged(active_image_);
          });

  connect(&image_manager_, &ImageManager::imageOpened, this,
          &MainWindow::showDisplayArea);

  connect(&image_manager_, &ImageManager::imageSaved, this,
          [this](const ProImage *image) {
            statusBar()->showMessage(
                QString("Saved image on %1").arg(image->filePath()), 2000);
          });

  connect(&image_manager_, &ImageManager::imageDuplicated, this,
          &MainWindow::showDisplayArea);
}

void MainWindow::showDisplayArea(const ProImage *image) {
  ImageDisplayArea *display_area = new ImageDisplayArea();

  display_area->setImage(image);
  mdi_area_->addSubWindow(display_area);
  display_area->show();

  connect(display_area, &ImageDisplayArea::pixelInformation,
          main_status_bar_->pixelInfoWidget(),
          &PixelInformationWidget::onPixelInformationReceived);
}

void MainWindow::createMenus() {
  // File menu
  file_menu_ = new FileMenu();
  menuBar()->addMenu(file_menu_);

  connect(file_menu_, &FileMenu::open, &image_manager_, &ImageManager::open);
  connect(file_menu_, &FileMenu::save, &image_manager_,
          [this] { image_manager_.save(active_image_); });
  connect(file_menu_, &FileMenu::saveAs, &image_manager_,
          [this] { image_manager_.saveAs(active_image_); });
  connect(file_menu_, &FileMenu::quit, qApp, &QApplication::quit);

  // Image menu
  image_menu_ = new ImageMenu();
  menuBar()->addMenu(image_menu_);

  connect(image_menu_, &ImageMenu::duplicateImage, &image_manager_,
          [this] { image_manager_.duplicate(active_image_); });
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
