#include "transpose.hpp"

namespace imagecpp {

Transpose::Transpose(Document *document) : PointOperation(document, tr("Transpose")) {}

QRgb Transpose::pointOperationImpl(int x, int y, QRgb) const {
  return oldImage()->pixel(y, x);
}

void Transpose::imageOperationImpl(Image *new_image) {
  new_image->reset(oldImage()->height(), oldImage()->width());

  for (int y = 0; y < new_image->height(); ++y) {
    QRgb *new_line = (QRgb *)new_image->scanLine(y);

    for (int x = 0; x < new_image->width(); ++x) {
      new_line[x] = pointOperationImpl(x, y, 0);
    }
  }
}

}  // namespace imagecpp
