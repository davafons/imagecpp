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
    setName(tr("Scale (%1 - %2)").arg(x_percentage).arg(y_percentage));
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

void Scale::imageOperationImpl(Image* new_image) {
  // Set the new scale of the image
  int new_width = oldImage()->width() * x_percentage / 100;
  int new_height = oldImage()->height() * y_percentage / 100;

  new_image->reset(new_width, new_height);

  for (int y = 0; y < new_image->height(); ++y) {
    QRgb* new_line = (QRgb*)new_image->scanLine(y);

    for (int x = 0; x < new_image->width(); ++x) {
      new_line[x] = pointOperationImpl(x, y, 0);
    }
  }
}

QRgb Scale::pointOperationImpl(int x, int y, QRgb) {
  float original_x = float(x / (float(x_percentage) / 100));
  float original_y = float(y / (float(y_percentage) / 100));

  return nearestNeighbour(original_x, original_y, oldImage());
}

QRgb Scale::nearestNeighbour(float x, float y, const Image* old_image) const {
  int rounded_x = std::round(x);
  int rounded_y = std::round(y);

  return old_image->pixel(x, y);
}

}  // namespace imagecpp
