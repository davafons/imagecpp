#include "image.hpp"

#include <QDebug>

namespace imagecpp {

Image::Image(const QString &file_path) { open(file_path); }

Image::Image(int width, int height, QImage::Format format)
    : image_(width, height, format) {}

Image::Image(const Image &other) { image_ = other.image_.copy(); }

Image::Image(Image &&other) { swap(*this, other); }

Image &Image::operator=(Image other) {
  swap(*this, other);

  return *this;
}

QPixmap Image::getPixmap() const noexcept {
  return QPixmap::fromImage(image_);
}

Image *Image::copy() const { return new Image(*this); }

void swap(Image &first, Image &second) noexcept {
  using std::swap;

  swap(first.image_, second.image_);
}

void Image::open(const QString &file_path) { image_ = QImage(file_path); }

bool Image::saveAs(const QString &file_path) const {
  return image_.save(file_path);
}

Image *Image::empty(const Image &other) {
  return new Image(other.width(), other.height(), other.format());
}

} // namespace imagecpp
