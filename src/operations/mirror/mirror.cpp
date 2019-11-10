#include "mirror.hpp"

namespace imagecpp {

Mirror::Mirror(Document* document, const Direction& dir)
    : PointOperation(document, tr("Mirror")), dir_(dir) {}

Mirror::Direction Mirror::direction() const {
  return dir_;
}

void Mirror::setDirection(const Direction& dir) {
  dir_ = dir;

  emit propertyChanged();
}

QRgb Mirror::pointOperationImpl(int x, int y, QRgb color) const {
  switch (dir_) {
    case Direction::Horizontal:
      return oldImage()->pixel(oldImage()->width() - x - 1, y);
      break;

    case Direction::Vertical:
      return oldImage()->pixel(x, oldImage()->height() - y - 1);
      break;

    default:
      return color;
      break;
  }
}

}  // namespace imagecpp
