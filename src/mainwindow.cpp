#include "mainwindow.hpp"
#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"
#include "manager/imagemanager.hpp"
#include "menus/editmenu.hpp"
#include "menus/filemenu.hpp"
#include "menus/imagemenu.hpp"
#include "operations/color.hpp"
#include "statusbar/mainstatusbar.hpp"

#include <QApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QUndoGroup>
#include <QUndoView>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : mdi_area_(new QMdiArea()), undo_group_(new QUndoGroup()),
      QMainWindow(parent, flags) {
  createMenus();
  createStatusBar();

  mdi_area_->setTabsClosable(true);
  mdi_area_->setTabsMovable(true);

  QUndoView *undo_view = new QUndoView();
  undo_view->setGroup(undo_group_);

  setCentralWidget(mdi_area_);

  QDockWidget *dock = new QDockWidget(tr("History"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(undo_view);
  addDockWidget(Qt::RightDockWidgetArea, dock);

  connect(mdi_area_, &QMdiArea::subWindowActivated, this,
          [this](const QMdiSubWindow *w) {
            active_image_ = activeImage();
            if (active_image_) {
              undo_group_->setActiveStack(&active_image_->undoStack());
              qDebug() << undo_group_->activeStack();
            }
            emit activeImageChanged(active_image_);
          });

  connect(&image_manager_, &ImageManager::imageOpened, this,
          &MainWindow::showDisplayArea);
  connect(
      &image_manager_, &ImageManager::imageOpened, this,
      [this](ProImage *image) { undo_group_->addStack(&image->undoStack()); });

  connect(&image_manager_, &ImageManager::imageSaved, this,
          [this](const ProImage *image) {
            statusBar()->showMessage(
                QString("Saved image on %1").arg(image->filePath()), 2000);
          });

  connect(&image_manager_, &ImageManager::imageDuplicated, this,
          &MainWindow::showDisplayArea);
}

MainWindow::~MainWindow() {

  delete mdi_area_;
  delete undo_group_;
}

void MainWindow::showDisplayArea(const ProImage *image) {
  ImageDisplayArea *display_area = new ImageDisplayArea();

  display_area->setImage(image);
  mdi_area_->addSubWindow(display_area);
  display_area->show();

  connect(display_area, &ImageDisplayArea::pixelInformation,
          main_status_bar_.pixelInfoWidget(),
          &PixelInformationWidget::onPixelInformationReceived);
}

void MainWindow::createMenus() {
  // File menu
  menuBar()->addMenu(&file_menu_);

  connect(&file_menu_, &FileMenu::open, &image_manager_, &ImageManager::open);
  connect(&file_menu_, &FileMenu::save, &image_manager_,
          [this] { image_manager_.save(active_image_); });
  connect(&file_menu_, &FileMenu::saveAs, &image_manager_,
          [this] { image_manager_.saveAs(active_image_); });

  connect(&file_menu_, &FileMenu::closeView, mdi_area_,
          &QMdiArea::closeActiveSubWindow);
  connect(&file_menu_, &FileMenu::closeAll, mdi_area_,
          &QMdiArea::closeAllSubWindows);
  connect(&file_menu_, &FileMenu::quit, qApp, &QApplication::quit);

  // Edit menu
  menuBar()->addMenu(&edit_menu_);
  edit_menu_.createUndoActions(undo_group_);

  connect(&edit_menu_, &EditMenu::undo, undo_group_, &QUndoGroup::undo);
  connect(&edit_menu_, &EditMenu::redo, undo_group_, &QUndoGroup::redo);

  // Image menu
  menuBar()->addMenu(&image_menu_);

  connect(&image_menu_, &ImageMenu::duplicateImage, &image_manager_,
          [this] { image_manager_.duplicate(active_image_); });

  connect(&image_menu_, &ImageMenu::toGrayscale, this, [this] {
    if (active_image_) {
      active_image_->runCommand(new ToGrayscaleCommand(active_image_));
    }
  });
}

void MainWindow::createStatusBar() { setStatusBar(&main_status_bar_); }

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
