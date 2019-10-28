#include "grayscale.hpp"

#include <QGroupBox>
#include <QRadioButton>

namespace imagecpp {

/*!
 *  \class Grayscale
 *  \brief Transforms an image to grayscale.
 *
 *  Can be used with both PAL and NTSC formulas.
 */

/*!
 *  Construcs a Grayscale operation object.
 */
Grayscale::Grayscale(Document *document) : PixelOperation(document) {

  // Update the operation name each time a property changes
  connect(this, &Grayscale::propertyChanged, this, [this] {
    setName(tr("Grayscale (%1)").arg((format_ == Format::PAL) ? "PAL" : "NTSC"));
  });

  // Default format used for the grayscale formula
  setFormat(Format::PAL);
}

/*!
 *  Returns the format used by the grayscale operation.
 *
 *  \sa setFormat(const Format& format)
 */
Grayscale::Format Grayscale::format() const {
  return format_;
}

/*!
 *  Sets the RGB factors used by the grayscale formula, depending on the Format (PAL or
 *  NSTC)
 */
void Grayscale::setFormat(const Format &format) {
  format_ = format;

  red_factor_ = (format_ == Format::PAL) ? 0.222f : 0.299f;
  green_factor_ = (format_ == Format::PAL) ? 0.707f : 0.587f;
  blue_factor_ = (format_ == Format::PAL) ? 0.071f : 0.114f;

  emit propertyChanged();
}

/*!
 *  Implementation of the Grayscale operation.
 *
 *  For each pixel, multiply the input color with the RGB factors, and add them
 *  together. The result will be the intensity of the pixel, which must be placed on the
 *  three RGB channels.
 */
QRgb Grayscale::pixelOperationImpl(int, int, QRgb color) const {
  uint8_t red = qRed(color) * red_factor_;
  uint8_t green = qGreen(color) * green_factor_;
  uint8_t blue = qBlue(color) * blue_factor_;

  uint8_t gray = std::min(red + green + blue, 255);

  return qRgba(gray, gray, gray, qAlpha(color));
}

}  // namespace imagecpp
