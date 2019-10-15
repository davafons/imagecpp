#include "operations/private/lutoperation.hpp"

namespace imagecpp {

LutOperation::LutOperation(Document *document, const QString &name)
    : PixelOperation(document, name) {
  r_lut_.fill(0);
  g_lut_.fill(0);
  b_lut_.fill(0);
}

QRgb LutOperation::pixelOperation(int x, int y, QRgb color) const {
  return qRgba(r_lut_[qRed(color)], g_lut_[qGreen(color)], b_lut_[qBlue(color)],
               qAlpha(color));
}

void LutOperation::generateTargetImage() {
  qDebug() << "Called LutOperation generate Image";
  fillLutTables();

  // Continue with parent
  ImageOperation::generateTargetImage();
}

} // namespace imagecpp
