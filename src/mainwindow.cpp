#include "mainwindow.hpp"
#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"
#include "menus/filemenu.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QMdiArea>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), mdi_area_(new QMdiArea()) {
  createMenus();
  connectMenus();

  setStatusBar(statusBar());

  mdi_area_->setTabsClosable(true);
  mdi_area_->setTabsMovable(true);

  setCentralWidget(mdi_area_);
}

void MainWindow::createMenus() {
  file_menu_ = new FileMenu();
  menuBar()->addMenu(file_menu_);
}

void MainWindow::connectMenus() {
  // File Menu
  connect(file_menu_->openAct(), &QAction::triggered, this, &MainWindow::open);
  connect(file_menu_->saveAct(), &QAction::triggered, this, &MainWindow::save);
  connect(file_menu_->quitAct(), &QAction::triggered, qApp,
          &QApplication::quit);
}

void MainWindow::open() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  if (!file_path.isEmpty()) {
    addImageDisplayArea(new ProImage(file_path));
  }
}

void MainWindow::save() {}

void MainWindow::addImageDisplayArea(const ProImage *image) {
  ImageDisplayArea *display_area = new ImageDisplayArea();
  display_area->setImage(image);

  mdi_area_->addSubWindow(display_area);
  display_area->show();
}
