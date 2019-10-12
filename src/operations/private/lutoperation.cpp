#include "operations/private/lutoperation.hpp"

namespace imagecpp {

LutOperation::LutOperation(Document *document, const QString &name)
    : PixelOperation(document, name) {
  fillLutTables();
}

void LutOperation::fillLutTables() {
  r_lut_.fill(0);
  g_lut_.fill(0);
  b_lut_.fill(0);
}

QRgb LutOperation::pixelOperation(int x, int y, QRgb color) const {
  return qRgba(r_lut_[qRed(color)], g_lut_[qGreen(color)], b_lut_[qBlue(color)],
               qAlpha(color));
}

} // namespace imagecpp
