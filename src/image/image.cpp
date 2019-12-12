#include "image.hpp"

#include <QDebug>

namespace imagecpp {

// Construction and copy
Image::Image(const QString &file_path) {
  open(file_path);
}
Image::Image(const QImage &image) : image_(image) {}

Image::Image(int width, int height, QImage::Format format)
    : image_(width, height, format) {}

Image::Image(const Image &other) {
  image_ = other.image_.copy();
}

Image::Image(Image &&other) {
  swap(*this, other);
}

Image &Image::operator=(Image other) {
  swap(*this, other);

  return *this;
}

void Image::setImage(const Image &other) {
  image_ = other.image_.copy();
}

// Image Operations
QPixmap Image::getPixmap() const noexcept {
  return QPixmap::fromImage(image_);
}
Image *Image::copy(const QRect &rectangle) const {
  return new Image(image_.copy(rectangle));
}

void Image::reset(int width, int height) {
  image_ = QImage(width, height, format());
}

// Iterators
// QRgb *Image::begin() { return (QRgb *)image_.bits(); }
// const QRgb *Image::begin() const { return cbegin(); }
// const QRgb *Image::cbegin() const { return (QRgb *)image_.constBits(); }
//
// QRgb *Image::end() { return (QRgb *)(image_.bits() + pixelCount()); }
// const QRgb *Image::end() const { return cend(); }
// const QRgb *Image::cend() const {
//   return (QRgb *)(image_.constBits() + pixelCount());
// }

// Properties
int Image::width() const noexcept {
  return image_.width();
}
int Image::height() const noexcept {
  return image_.height();
}
QSize Image::size() const noexcept {
  return image_.size();
}
QRect Image::rect() const noexcept {
  return image_.rect();
}
QImage::Format Image::format() const noexcept {
  return image_.format();
}
size_t Image::pixelCount() const noexcept {
  return image_.width() * image_.height();
}

// Pixel Operations
QRgb *Image::bits() {
  return (QRgb *)image_.bits();
}
QRgb *Image::scanLine(int i) {
  return (QRgb *)image_.scanLine(i);
}
const QRgb *Image::constBits() const {
  return (QRgb *)image_.constBits();
}
const QRgb *Image::constScanLine(int i) const {
  return (QRgb *)image_.constScanLine(i);
}

QRgb Image::pixel(int x, int y) const {
  return image_.pixel(x, y);
}
QRgb Image::pixel(const QPoint &position) const {
  return image_.pixel(position);
}

void Image::setPixel(int x, int y, uint index_or_rgb) {
  image_.setPixel(x, y, index_or_rgb);
}
void Image::setPixel(const QPoint &position, uint index_or_rgb) {
  image_.setPixel(position, index_or_rgb);
}

void Image::fill(const QColor &color) {
  image_.fill(color);
}

QColor Image::pixelColor(const QPoint &position) const {
  return image_.pixelColor(position);
}

QColor Image::pixelColor(int x, int y) const {
  return image_.pixelColor(x, y);
}

void Image::setPixelColor(int x, int y, const QColor &color) {
  image_.setPixelColor(x, y, color);
}
void Image::setPixelColor(const QPoint &position, const QColor &color) {
  image_.setPixelColor(position, color);
}

// Static functions
Image *Image::empty(const Image &other) {
  return new Image(other.width(), other.height(), other.format());
}

Image *Image::empty(size_t width, size_t height, QImage::Format format) {
  return new Image(width, height, format);
}

// Friend functions
void swap(Image &first, Image &second) noexcept {
  using std::swap;

  swap(first.image_, second.image_);
}

// Slots
void Image::open(const QString &file_path) {
  image_ = QImage(file_path);
  image_.convertTo(QImage::Format_ARGB32);
}

bool Image::saveAs(const QString &file_path) const {
  return image_.save(file_path);
}

}  // namespace imagecpp
