#include "color.hpp"

#include <QColor>

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

ToGrayscaleCommand::ToGrayscaleCommand(ImageData *data)
    : ImageOperation(data) {
  // Show dialog to select between Pal and Ntsc
  Format format = Format::PAL;

  red_factor_ = (format == Format::PAL) ? 0.222f : 0.299f;
  green_factor_ = (format == Format::PAL) ? 0.707f : 0.587f;
  blue_factor_ = (format == Format::PAL) ? 0.071f : 0.114f;

  setOperationName(QString("To Grayscale (%1)")
                       .arg((format == Format::PAL) ? "PAL" : "NTSC"));
}

QRgb ToGrayscaleCommand::pixelOperation(int, int, QRgb color) const {
  uint8_t red = qRed(color) * red_factor_;
  uint8_t green = qGreen(color) * green_factor_;
  uint8_t blue = qBlue(color) * blue_factor_;

  uint8_t gray = std::min(red + green + blue, 255);

  return qRgba(gray, gray, gray, qAlpha(color));
}
