#include "color.hpp"

#include <QColor>
#include <QDialog>

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

ToGrayscaleOperation::ToGrayscaleOperation(ImageData *data,
                                           const Format &format)
    : ImageOperation(data) {
  setFormat(format);
}

ToGrayscaleOperation &ToGrayscaleOperation::setFormat(const Format &format) {
  format_ = format;

  red_factor_ = (format_ == Format::PAL) ? 0.222f : 0.299f;
  green_factor_ = (format_ == Format::PAL) ? 0.707f : 0.587f;
  blue_factor_ = (format_ == Format::PAL) ? 0.071f : 0.114f;

  setName(QString("To Grayscale (%1)")
              .arg((format == Format::PAL) ? "PAL" : "NTSC"));

  emit propertyChanged();

  return *this;
}

QRgb ToGrayscaleOperation::pixelOperation(int, int, QRgb color) const {
  uint8_t red = qRed(color) * red_factor_;
  uint8_t green = qGreen(color) * green_factor_;
  uint8_t blue = qBlue(color) * blue_factor_;

  uint8_t gray = std::min(red + green + blue, 255);

  return qRgba(gray, gray, gray, qAlpha(color));
}
