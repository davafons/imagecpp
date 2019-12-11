#include "scale.hpp"

namespace imagecpp {

/*!
 *  \class Scale
 *  \brief Scale an image to the desired size.
 */

/*!
 *  Construct a Scale operation object.
 */

Scale::Scale(Document* document) : PointOperation(document) {
  // Update the operation name each time a property changes
  connect(this, &Scale::propertyChanged, this, [this] {
    setName(tr("Scale (%1 - %2)").arg(x_percentage, y_percentage));
  });
}

int Scale::scaleX() const {
  return x_percentage;
}

int Scale::scaleY() const {
  return y_percentage;
}

void Scale::setScaleX(int percentage) {
  x_percentage = percentage;

  emit propertyChanged();
}

void Scale::setScaleY(int percentage) {
  y_percentage = percentage;

  emit propertyChanged();
}

QRgb Scale::pointOperationImpl(int, int, QRgb color) {
  return color;
}

}  // namespace imagecpp
