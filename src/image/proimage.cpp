#include "proimage.hpp"

#include <QDebug>
#include <QUndoCommand>
#include <QUndoStack>

ProImage::ProImage(QObject *parent) : QObject(parent) {}

ProImage::ProImage(const QString &file_path, QObject *parent)
    : ProImage(parent) {
  open(file_path);
}

ProImage::ProImage(const ProImage &other) { image_ = other.image_.copy(); }

ProImage::ProImage(ProImage &&other) { swap(*this, other); }

ProImage &ProImage::operator=(ProImage other) {
  swap(*this, other);

  return *this;
}

QPixmap ProImage::getPixmap() const noexcept {
  return QPixmap::fromImage(image_);
}

QSize ProImage::size() const noexcept { return image_.size(); }

QRgb ProImage::pixel(int x, int y) const { return image_.pixel(x, y); }

QRgb ProImage::pixel(const QPoint &position) const {
  return image_.pixel(position);
}

QRect ProImage::rect() const noexcept { return image_.rect(); }

void swap(ProImage &first, ProImage &second) noexcept {
  using std::swap;

  swap(first.image_, second.image_);
}

void ProImage::open(const QString &file_path) { image_ = QImage(file_path); }

bool ProImage::saveAs(const QString &file_path) const {
  return image_.save(file_path);
}
