#include "mainwindow.hpp"

#include <QApplication>
#include <QDockWidget>
#include <QMenuBar>
#include <QUndoGroup>
#include <QUndoView>

#include "widgets/image/imagedisplayarea.hpp"
#include "widgets/image/subwindowsarea.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : mdi_area_(new SubWindowsArea()), undo_group_(new QUndoGroup()),
      QMainWindow(parent, flags) {
  createMenus();
  createStatusBar();

  // MdiArea
  setCentralWidget(mdi_area_);

  connect(mdi_area_, &SubWindowsArea::displayAreaAdded, this,
          [this](ImageDisplayArea *d) {
            connect(d, &ImageDisplayArea::pixelInformation,
                    main_status_bar_.pixelInfoWidget(),
                    &PixelInformationWidget::onPixelInformationReceived);
          });

  // UndoView
  QUndoView *undo_view = new QUndoView();
  undo_view->setGroup(undo_group_);

  // Docks
  QDockWidget *dock = new QDockWidget(tr("History"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(undo_view);
  addDockWidget(Qt::RightDockWidgetArea, dock);

  // ImageManager
  connect(&image_manager_, &ImageManager::imageOpened, mdi_area_,
          &SubWindowsArea::addDisplayArea);

  connect(&image_manager_, &ImageManager::imageOpened, this,
          [this](ImageData *image_data) {
            if (image_data) {
              undo_group_->addStack(image_data->undoStack());
            }
          });

  connect(&image_manager_, &ImageManager::imageSaved, this,
          [this](ImageData *, const QString &file_path) {
            statusBar()->showMessage(
                QString("Saved image on %1").arg(file_path), 2000);
          });
}

MainWindow::~MainWindow() {
  delete mdi_area_;
  delete undo_group_;
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
          &SubWindowsArea::closeActiveSubWindow);
  connect(&file_menu_, &FileMenu::closeAll, mdi_area_,
          &SubWindowsArea::closeAllSubWindows);
  connect(&file_menu_, &FileMenu::quit, qApp, &QApplication::quit);

  // Edit menu
  menuBar()->addMenu(&edit_menu_);
  edit_menu_.createUndoActions(undo_group_);

  connect(&edit_menu_, &EditMenu::undo, undo_group_, &QUndoGroup::undo);
  connect(&edit_menu_, &EditMenu::redo, undo_group_, &QUndoGroup::redo);

  // Image menu
  menuBar()->addMenu(&image_menu_);

  connect(&image_menu_, &ImageMenu::duplicateImage, &image_manager_, [this] {
    if (mdi_area_->activeImage()) {
      image_manager_.duplicate(mdi_area_->activeImage());
    }
  });

  // TODO: Complete
  connect(&image_menu_, &ImageMenu::toGrayscale, this, [this] {});
}

void MainWindow::createStatusBar() { setStatusBar(&main_status_bar_); }
