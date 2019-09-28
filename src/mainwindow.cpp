#include "mainwindow.hpp"
#include "imageviewarea.hpp"

#include <QApplication>
#include <QBitmap>
#include <QDebug>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QStatusBar>
#include <QString>

#include "histogram_view.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), mdi_area_(new QMdiArea()) {
  createActions();
  createMenus();
  setStatusBar(statusBar());

  colorLabel_ = new QLabel();
  colorLabel_->setFixedSize(QSize(16, 16));
  colorLabel_->setStyleSheet(
      "background-color: white; border: 1px solid black; ");

  pixelLabel_ = new QLabel();

  statusBar()->addWidget(colorLabel_);
  statusBar()->addWidget(pixelLabel_);

  mdi_area_->setTabsClosable(true);
  mdi_area_->setTabsMovable(true);

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

  zoom_in_act_ = new QAction(tr("Zoom in"));
  zoom_in_act_->setShortcut(QKeySequence::ZoomIn);

  connect(zoom_in_act_, &QAction::triggered, this, &MainWindow::zoomIn);

  zoom_out_act_ = new QAction(tr("Zoom out"));
  zoom_out_act_->setShortcut(QKeySequence::ZoomOut);

  connect(zoom_out_act_, &QAction::triggered, this, &MainWindow::zoomOut);

  normal_size_act_ = new QAction(tr("Reset to normal size"));
  connect(normal_size_act_, &QAction::triggered, this, &MainWindow::normalSize);
}

void MainWindow::createMenus() {
  file_menu_ = menuBar()->addMenu(tr("&File"));
  file_menu_->addAction(open_act_);
  file_menu_->addAction(save_act_);
  file_menu_->addAction(save_as_act_);
  file_menu_->addSeparator();
  file_menu_->addAction(quit_act_);

  options_menu_ = menuBar()->addMenu(tr("Options"));
  options_menu_->addAction(zoom_in_act_);
  options_menu_->addAction(zoom_out_act_);
  options_menu_->addAction(normal_size_act_);
  options_menu_->addSeparator();
  options_menu_->addAction(toggle_subtabs_act_);
}

ImageViewArea *MainWindow::getActiveImageViewArea() const {
  ImageViewArea *image_viewer = nullptr;

  QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow();
  if (active_subwindow) {
    image_viewer = dynamic_cast<ImageViewArea *>(active_subwindow->widget());
  }

  return image_viewer;
}

void MainWindow::pixelMouseOver(const QPoint &point, const QColor &color) {
  pixelLabel_->setText(QString("x: %1 y: %2 \t R: %3 G: %4 B: %5 A: %6")
                           .arg(point.x() + 1)
                           .arg(point.y() + 1)
                           .arg(color.red())
                           .arg(color.green())
                           .arg(color.blue())
                           .arg(color.alpha()));

  colorLabel_->setStyleSheet(
      QString("background-color: %1; border: 1px solid black;")
          .arg(color.name()));
  // TODO: Don't repeat "border" property again
}

// TODO: Move dialog to imageviewer ??
void MainWindow::open() {
  qDebug() << "MainWindow::open() called";

  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  if (!file_path.isEmpty()) {
    ImageViewArea *image_viewer = new ImageViewArea(file_path);

    // Add subwindow
    mdi_area_->addSubWindow(image_viewer);
    image_viewer->show();

    connect(image_viewer, &ImageViewArea::pixelInformation, this,
            &MainWindow::pixelMouseOver);

    // HistogramView *hist_view = new HistogramView(image_viewer->getHistogram());
    // QChartView *chartView = new QChartView(hist_view);
    // chartView->setRenderHint(QPainter::Antialiasing);
    // chartView->resize(400, 400);
    //
    // mdi_area_->addSubWindow(chartView);
    // chartView->show();
  }
}

void MainWindow::save() {
  qDebug() << "MainWindow::save() called";

  ImageViewArea *active_imageviewer = getActiveImageViewArea();

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

  ImageViewArea *active_imageviewer = getActiveImageViewArea();

  if (!active_imageviewer) {
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Select a window with an image!"));
    return;
  }

  // TODO: Enforce save with image extension
  QString file_path = QFileDialog::getSaveFileName(
      this, tr("Save Image"), "~", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

  qDebug() << "Image to save path:" << file_path;

  if (!file_path.isEmpty() && !active_imageviewer->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    QMessageBox::critical(this, tr("Save As... error"),
                          tr("Couldn't save image!"));
  }
}

void MainWindow::zoomIn() {
  ImageViewArea *active_imageviewer = getActiveImageViewArea();
  if (active_imageviewer) {
    active_imageviewer->zoomIn();
  }
}

void MainWindow::zoomOut() {
  ImageViewArea *active_imageviewer = getActiveImageViewArea();
  if (active_imageviewer) {
    active_imageviewer->zoomOut();
  }
}

void MainWindow::normalSize() {
  ImageViewArea *active_imageviewer = getActiveImageViewArea();
  if (active_imageviewer) {
    active_imageviewer->normalSize();
  }
}
