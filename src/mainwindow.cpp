#include "mainwindow.hpp"

#include <QDockWidget>
#include <QUndoGroup>
#include <QUndoView>
#include <QMenuBar>
#include <QApplication>

#include "widgets/image/imagedisplayarea.hpp"
#include "widgets/image/subwindowsarea.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : mdi_area_(new SubWindowsArea()), undo_group_(new QUndoGroup()),
      QMainWindow(parent, flags) {
  createMenus();
  createStatusBar();

  // UndoView
  QUndoView *undo_view = new QUndoView();
  undo_view->setGroup(undo_group_);

  setCentralWidget(mdi_area_);

  // Docks
  QDockWidget *dock = new QDockWidget(tr("History"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(undo_view);
  addDockWidget(Qt::RightDockWidgetArea, dock);

  connect(&image_manager_, &ImageManager::imageOpened, mdi_area_,
          &SubWindowsArea::addDisplayArea);

  connect(mdi_area_, &SubWindowsArea::displayAreaAdded, this,
          [this](ImageDisplayArea *d) {
            connect(d, &ImageDisplayArea::pixelInformation,
                    main_status_bar_.pixelInfoWidget(),
                    &PixelInformationWidget::onPixelInformationReceived);
          });

  connect(
      &image_manager_, &ImageManager::imageOpened, this,
      [this](ImageData
                 *image) { /* undo_group_->addStack(&image->undoStack()); */ });

  connect(&image_manager_, &ImageManager::imageSaved, this,
          [this](ImageData *image, const QString &file_path) {
            statusBar()->showMessage(
                QString("Saved image on %1").arg(file_path), 2000);
          });

  connect(&image_manager_, &ImageManager::imageDuplicated, this,
          &MainWindow::showDisplayArea);
}

MainWindow::~MainWindow() {

  delete mdi_area_;
  delete undo_group_;
}

void MainWindow::showDisplayArea(ImageData *data) {
  mdi_area_->addDisplayArea(data);
}

void MainWindow::createMenus() {
  // File menu
  menuBar()->addMenu(&file_menu_);

  connect(&file_menu_, &FileMenu::open, &image_manager_, &ImageManager::open);
  connect(&file_menu_, &FileMenu::save, &image_manager_, [this] {
    if (mdi_area_->activeImage()) {
      image_manager_.save(mdi_area_->activeImage());
    }
  });
  connect(&file_menu_, &FileMenu::saveAs, &image_manager_, [this] {
    if (mdi_area_->activeImage()) {
      image_manager_.saveAs(mdi_area_->activeImage());
    }
  });

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
          [this] { /* image_manager_.duplicate(active_image_); */ });

  // TODO: Complete
  connect(&image_menu_, &ImageMenu::toGrayscale, this, [this] {});
}

void MainWindow::createStatusBar() { setStatusBar(&main_status_bar_); }
