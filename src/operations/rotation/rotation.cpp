#include "rotation.hpp"

namespace imagecpp {

Rotation::Rotation(Document *document) : PointOperation(document, tr("Rotation")) {}

int Rotation::degrees() const {
  return degrees_;
}

void Rotation::setDegrees(int degrees) {
  degrees_ = (360 + (degrees % 360)) % 360;

  emit propertyChanged();
}

QRgb Rotation::pointOperationImpl(int x, int y, QRgb) {
  switch (degrees_) {
    case 90:
      return oldImage()->pixel(y, oldImage()->height() - x - 1);
      break;

    case 180:
      return oldImage()->pixel(oldImage()->width() - x - 1,
                               oldImage()->height() - y - 1);
      break;

    case 270:
      return oldImage()->pixel(oldImage()->width() - y - 1, x);
      break;

    default:
      return oldImage()->pixel(x, y);
      break;
  }
}

void Rotation::imageOperationImpl(Image *new_image) {
  if (degrees_ % 360 == 90 || degrees_ % 360 == 270) {
    new_image->reset(oldImage()->height(), oldImage()->width());
  } else {
    new_image->reset(oldImage()->width(), oldImage()->height());
  }

  for (int y = 0; y < new_image->height(); ++y) {
    QRgb *new_line = (QRgb *)new_image->scanLine(y);

    for (int x = 0; x < new_image->width(); ++x) {
      new_line[x] = pointOperationImpl(x, y, 0);
    }
  }
}

}  // namespace imagecpp
