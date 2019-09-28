#include "imageviewarea.hpp"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPalette>
#include <QPixmap>
#include <QScrollBar>

#include "histogram_model.hpp"

ImageViewArea::ImageViewArea(QWidget *parent) {
  setBackgroundRole(QPalette::Dark);
  setWidget(display_);

  connect(display_, &ImageDisplay::pixelInformation, this,
          &ImageViewArea::pixelInformation);

  // connect(display_, &ImageDisplay::scaleFactorChanged, this,
  //         &ImageViewArea::adjustScrollBars);
}

ImageViewArea::ImageViewArea(const QString &file_path, QWidget *parent)
    : ImageViewArea(parent) {
  open(file_path);
}

ImageViewArea::~ImageViewArea() {
  delete histogram_;
  delete loaded_image_;
}

void ImageViewArea::open(const QString &file_path) {
  qDebug() << "ImageViewArea::open() called with" << file_path;

  loaded_image_ = new QImage(file_path);
  display_->setImage(loaded_image_);

  file_path_ = file_path;
  setWindowTitle(file_path_);

  // Build the histogram
  histogram_ = new HistogramModel(loaded_image_);
}

bool ImageViewArea::save() const { return saveAs(file_path_); }

bool ImageViewArea::saveAs(const QString &file_path) const {
  qDebug() << "ImageViewArea::saveAs() called";

  return loaded_image_->save(file_path);
}
//
// void ImageViewArea::adjustScrollBars(float scale_factor) {
//   auto adjustScrollBar = [](QScrollBar *scroll_bar, float scale_factor) {
//     scroll_bar->setValue(
//         int(scale_factor * scroll_bar->value() +
//             ((scale_factor - 1) * scroll_bar->pageStep() / 2)));
//   };
//
//   // adjustScrollBar(horizontalScrollBar(), scale_factor);
//   // adjustScrollBar(verticalScrollBar(), scale_factor);
// }

void ImageViewArea::zoomIn() { display_->zoomIn(); }
void ImageViewArea::zoomOut() { display_->zoomOut(); }
void ImageViewArea::normalSize() { display_->normalSize(); }
