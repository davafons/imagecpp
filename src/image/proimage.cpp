#include "proimage.hpp"

#include <QDebug>
#include <QUndoCommand>
#include <QUndoStack>

ProImage::ProImage(const QString &file_path) { open(file_path); }

ProImage::ProImage(int width, int height, QImage::Format format)
    : image_(width, height, format) {}

ProImage::ProImage(const ProImage &other) { image_ = other.image_.copy(); }

ProImage::ProImage(ProImage &&other) { swap(*this, other); }

ProImage &ProImage::operator=(ProImage other) {
  swap(*this, other);

  return *this;
}

QPixmap ProImage::getPixmap() const noexcept {
  return QPixmap::fromImage(image_);
}

ProImage *ProImage::copy() const { return new ProImage(*this); }

void swap(ProImage &first, ProImage &second) noexcept {
  using std::swap;

  swap(first.image_, second.image_);
}

void ProImage::open(const QString &file_path) { image_ = QImage(file_path); }

bool ProImage::saveAs(const QString &file_path) const {
  return image_.save(file_path);
}

ProImage *ProImage::empty(const ProImage &other) {
  return new ProImage(other.width(), other.height(), other.format());
}
