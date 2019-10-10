#include "operations/private/pixeloperation.hpp"

namespace imagecpp {
PixelOperation::PixelOperation(Document *data, const QString &name)
    : ImageOperation(data, name) {}

void PixelOperation::applyImageOperation() {
  for (int y = 0; y < target_image_->height(); ++y) {
    for (int x = 0; x < target_image_->width(); ++x) {
      target_image_->setPixel(x, y,
                              pixelOperation(x, y, old_image_->pixel(x, y)));
    }
  }
}

} // namespace imagecpp
