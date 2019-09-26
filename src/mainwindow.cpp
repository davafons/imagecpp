#include "mainwindow.hpp"
#include "imageviewer.hpp"

#include <QApplication>
#include <QBitmap>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
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

  connect(open_act_, &QAction::triggered, this, &MainWindow::openImage);

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
  file_menu_->addSeparator();
  file_menu_->addAction(quit_act_);

  options_menu_ = menuBar()->addMenu(tr("Options"));
  options_menu_->addAction(toggle_subtabs_act_);
}

void MainWindow::openImage() {
  qDebug() << "openImage() slot called";

  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.bmp)"));

  if (!file_path.isEmpty()) {
    ImageViewer *image_viewer = new ImageViewer(file_path);

    // Add subwindow
    mdi_area_->addSubWindow(image_viewer);
    image_viewer->show();
  }
}
