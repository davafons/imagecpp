#include "imageviewer.hpp"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPalette>
#include <QPixmap>

#include "histogram_model.hpp"

ImageViewer::ImageViewer(QWidget *parent) {
  setBackgroundRole(QPalette::Base);
  setWidget(display_);
}

ImageViewer::ImageViewer(const QString &file_path, QWidget *parent)
    : ImageViewer(parent) {
  open(file_path);
}

ImageViewer::~ImageViewer() { delete histogram_; }

void ImageViewer::open(const QString &file_path) {
  qDebug() << "ImageViewer::open() called with" << file_path;

  loaded_image_ = QImage(file_path);

  display_->setPixmap(QPixmap::fromImage(loaded_image_));
  display_->resize(loaded_image_.size());

  file_path_ = file_path;
  setWindowTitle(file_path_);

  // Build the histogram
  histogram_ = new HistogramModel(loaded_image_);
}

bool ImageViewer::save() const { return saveAs(file_path_); }

bool ImageViewer::saveAs(const QString &file_path) const {
  qDebug() << "ImageViewer::saveAs() called";

  return loaded_image_.save(file_path);
}

// TODO: Only emit while hovering the image, not the whole area
void ImageViewer::mouseMoveEvent(QMouseEvent *event) {
  emit pixelInformation(event->pos(), loaded_image_.pixel(event->pos()));
}
