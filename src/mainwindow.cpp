#include "mainwindow.hpp"
#include "imageviewer.hpp"

#include <QApplication>
#include <QBitmap>
#include <QDebug>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QStatusBar>
#include <QString>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), mdi_area_(new QMdiArea()) {
  createActions();
  createMenus();
  setStatusBar(statusBar());

  setCentralWidget(mdi_area_);
}

void MainWindow::createActions() {
  quit_act_ = new QAction(tr("&Quit"), this);
  quit_act_->setShortcut(QKeySequence::Quit);
  quit_act_->setStatusTip(tr("Quit from the application"));

  connect(quit_act_, &QAction::triggered, qApp, &QApplication::quit);

  open_act_ = new QAction(tr("&Open"), this);
  open_act_->setShortcut(QKeySequence::Open);
  open_act_->setStatusTip(tr("Open an image"));

  connect(open_act_, &QAction::triggered, this, &MainWindow::open);

  save_act_ = new QAction(tr("&Save"), this);
  save_act_->setShortcut(QKeySequence::Save);
  save_act_->setStatusTip(tr("Save current image"));

  connect(save_act_, &QAction::triggered, this, &MainWindow::save);

  save_as_act_ = new QAction(tr("&Save As..."), this);
  save_as_act_->setShortcut(QKeySequence::SaveAs);
  save_as_act_->setStatusTip(tr("Save current image as a new image"));

  connect(save_as_act_, &QAction::triggered, this, &MainWindow::saveAs);

  toggle_subtabs_act_ = new QAction(tr("Toggle tabs view"));
  toggle_subtabs_act_->setCheckable(true);
  toggle_subtabs_act_->setShortcut(Qt::CTRL + Qt::Key_T);
  toggle_subtabs_act_->setStatusTip(tr("Show subwindows as tabs"));

  connect(toggle_subtabs_act_, &QAction::triggered, mdi_area_,
          [this](bool checked) {
            (checked) ? mdi_area_->setViewMode(QMdiArea::TabbedView)
                      : mdi_area_->setViewMode(QMdiArea::SubWindowView);
          });
}

void MainWindow::createMenus() {
  file_menu_ = menuBar()->addMenu(tr("&File"));
  file_menu_->addAction(open_act_);
  file_menu_->addAction(save_act_);
  file_menu_->addAction(save_as_act_);
  file_menu_->addSeparator();
  file_menu_->addAction(quit_act_);

  options_menu_ = menuBar()->addMenu(tr("Options"));
  options_menu_->addAction(toggle_subtabs_act_);
}

ImageViewer *MainWindow::getActiveImageViewer() const {
  ImageViewer *image_viewer = nullptr;

  QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow();
  if (active_subwindow) {
    image_viewer = dynamic_cast<ImageViewer *>(active_subwindow->widget());
  }

  return image_viewer;
}

// TODO: Move dialog to imageviewer ??
void MainWindow::open() {
  qDebug() << "MainWindow::open() called";

  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.bmp)"));

  if (!file_path.isEmpty()) {
    ImageViewer *image_viewer = new ImageViewer(file_path);

    // Add subwindow
    mdi_area_->addSubWindow(image_viewer);
    image_viewer->show();
  }
}

void MainWindow::save() {
  qDebug() << "MainWindow::save() called";

  ImageViewer *active_imageviewer = getActiveImageViewer();

  // TODO: Remove code duplication
  if (!active_imageviewer) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  if (active_imageviewer->save()) {
    statusBar()->showMessage(
        QString("Saved image on %1").arg(active_imageviewer->getFilePath()));
  } else {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  }
}

void MainWindow::saveAs() {
  qDebug() << "MainWindow::saveAs() called";

  ImageViewer *active_imageviewer = getActiveImageViewer();

  if (!active_imageviewer) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  // TODO: Enforce save with image extension
  QString file_path = QFileDialog::getSaveFileName(
      this, tr("Save Image"), "~", tr("Image Files(*.png *.jpg *.bmp)"));

  qDebug() << "Image to save path:" << file_path;

  if (!file_path.isEmpty() && !active_imageviewer->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  }
}
