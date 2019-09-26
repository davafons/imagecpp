#include "imageviewer.hpp"

#include <QDebug>
#include <QPalette>
#include <QPixmap>

ImageViewer::ImageViewer(QWidget *parent) {
  setBackgroundRole(QPalette::Base);
  setWidget(display_);
}

ImageViewer::ImageViewer(const QString &file_path, QWidget *parent)
    : ImageViewer(parent) {
  openImage(file_path);
}

void ImageViewer::openImage(const QString &file_path) {
  qDebug() << QString("Open image: %1").arg(file_path);

  loaded_image_ = QImage(file_path);

  display_->setPixmap(QPixmap::fromImage(loaded_image_));
  display_->resize(loaded_image_.size());

  file_path_ = file_path;
  setWindowTitle(file_path_);
}
