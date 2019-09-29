#include "proimage.hpp"

ProImage::ProImage(const QString &file_path) {
  setFilePath(file_path);

  open(file_path_);
}

QPixmap ProImage::getPixmap() const { return QPixmap::fromImage(image_); }

QString ProImage::filePath() const { return file_path_; }

QSize ProImage::size() const { return image_.size(); }

QRgb ProImage::pixel(int x, int y) const { return image_.pixel(x, y); }

QRgb ProImage::pixel(const QPoint &position) const {
  return image_.pixel(position);
}

QRect ProImage::rect() const { return image_.rect(); }

void ProImage::open(const QString &file_path) {
  setFilePath(file_path);
  image_ = QImage(file_path);
}

bool ProImage::save() const { return saveAs(file_path_); }

bool ProImage::saveAs(const QString &file_path) const {
  return image_.save(file_path);
}

void ProImage::setFilePath(const QString &file_path) {
  file_path_ = file_path;

  emit filePathChanged(file_path);
}
