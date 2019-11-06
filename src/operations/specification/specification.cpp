#include "specification.hpp"

namespace imagecpp {

Specification::Specification(Document* document)
    : PointOperation(document, tr("Specification")) {
  auto h = oldHistogram().red().cummulativeBarsNormalized();

  for (int i = 0; i < 256; ++i) {
    qDebug() << h->at(i);
  }
}

QRgb Specification::pointOperationImpl(int, int, QRgb color) const {
  return color;
}

}  // namespace imagecpp
