#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QMenuBar>
#include <QUndoGroup>
#include <QUndoView>

#include "operations/color.hpp"
#include "widgets/image/imagedisplayarea.hpp"
#include "widgets/image/subwindowsarea.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : mdi_area_(new SubWindowsArea()), undo_group_(new QUndoGroup()),
      undo_view_(new QUndoView()), QMainWindow(parent, flags) {

  // Bars
  createMenuBar();
  createStatusBar();

  // UndoView
  undo_view_->setGroup(undo_group_);

  // MdiArea
  setCentralWidget(mdi_area_);

  connect(mdi_area_, &SubWindowsArea::displayAreaAdded, this,
          [this](ImageDisplayArea *d) {
            connect(d, &ImageDisplayArea::pixelInformation,
                    main_status_bar_.pixelInfoWidget(),
                    &PixelInformationWidget::onPixelInformationReceived);
          });

  connect(mdi_area_, &SubWindowsArea::activeImageChanged, this,
          [this](ImageData *image_data) {
            qInfo() << "Active image: " << image_data;
            if (image_data) {
              qInfo() << "Active stack: " << image_data->undoStack();
              undo_group_->setActiveStack(image_data->undoStack());
            }
          });

  // Docks
  QDockWidget *dock = new QDockWidget(tr("Tools"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(undo_view_);
  addDockWidget(Qt::RightDockWidgetArea, dock);

  // ImageManager
  connect(&image_manager_, &ImageManager::imageOpened, mdi_area_,
          &SubWindowsArea::addDisplayArea);

  connect(&image_manager_, &ImageManager::imageOpened, this,
          [this](ImageData *image_data) {
            Q_CHECK_PTR(image_data);
            if (image_data) {
              undo_group_->addStack(image_data->undoStack());
              qInfo() << "Add new undo stack: " << image_data->undoStack();
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
  delete undo_view_;
}

void MainWindow::createMenuBar() {
  setMenuBar(&main_menu_bar_);

  connect(&main_menu_bar_, &MainMenuBar::open, &image_manager_,
          &ImageManager::open);
  connect(&main_menu_bar_, &MainMenuBar::save, &image_manager_, [this] {
    if (mdi_area_->activeImage())
      image_manager_.save(mdi_area_->activeImage());
  });
  connect(&main_menu_bar_, &MainMenuBar::saveAs, &image_manager_, [this] {
    if (mdi_area_->activeImage())
      image_manager_.saveAs(mdi_area_->activeImage());
  });

  // TODO: Add "Save copy"

  connect(&main_menu_bar_, &MainMenuBar::closeView, mdi_area_,
          &SubWindowsArea::closeActiveSubWindow);
  connect(&main_menu_bar_, &MainMenuBar::closeAll, mdi_area_,
          &SubWindowsArea::closeAllSubWindows);
  connect(&main_menu_bar_, &MainMenuBar::quit, qApp, &QApplication::quit);

  connect(&main_menu_bar_, &MainMenuBar::undo, undo_group_, &QUndoGroup::undo);
  connect(&main_menu_bar_, &MainMenuBar::redo, undo_group_, &QUndoGroup::redo);

  connect(&main_menu_bar_, &MainMenuBar::duplicateImage, &image_manager_,
          [this] { image_manager_.duplicate(mdi_area_->activeImage()); });

  // TODO: Make better
  connect(&main_menu_bar_, &MainMenuBar::toGrayscale, &image_manager_, [this] {
    if (mdi_area_->activeImage()) {
      undo_group_->activeStack()->push(
          new ToGrayscaleCommand(mdi_area_->activeImage()));
    }
  });

  connect(&main_menu_bar_, &MainMenuBar::toggleTabsView, mdi_area_,
          &SubWindowsArea::toggleTabsView);
  connect(&main_menu_bar_, &MainMenuBar::toggleHistoryWindow, undo_view_,
          &SubWindowsArea::setVisible);
}

void MainWindow::createStatusBar() { setStatusBar(&main_status_bar_); }
