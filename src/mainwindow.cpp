#include "mainwindow.hpp"
#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"
#include "menus/filemenu.hpp"

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
  connectMenus();

  setStatusBar(statusBar());

  mdi_area_->setTabsClosable(true);
  mdi_area_->setTabsMovable(true);

  setCentralWidget(mdi_area_);
}

void MainWindow::open() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  if (!file_path.isEmpty()) {
    addImageDisplayArea(new ProImage(file_path));
  }
}

void MainWindow::save() {
  ImageDisplayArea *active_display = activeImageDisplayArea();

  // TODO: Remove code duplication
  if (!active_display) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  QExplicitlySharedDataPointer<const ProImage> image = active_display->image();

  if (image->save()) {
    statusBar()->showMessage(
        QString("Saved image on %1").arg(image->filePath()));
  } else {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  }
}

void MainWindow::addImageDisplayArea(const ProImage *image) {
  ImageDisplayArea *display_area = new ImageDisplayArea();
  display_area->setImage(image);

  mdi_area_->addSubWindow(display_area);
  display_area->show();
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

ImageDisplayArea *MainWindow::activeImageDisplayArea() const {
  ImageDisplayArea *display_area = nullptr;

  QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow();
  if (active_subwindow) {
    display_area = dynamic_cast<ImageDisplayArea *>(active_subwindow->widget());
  }

  return display_area;
}
