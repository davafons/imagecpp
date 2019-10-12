#include "operations/private/pixeloperation.hpp"

#include <QElapsedTimer>

namespace imagecpp {
PixelOperation::PixelOperation(Document *data, const QString &name)
    : ImageOperation(data, name) {}

void PixelOperation::applyImageOperation() {
  QElapsedTimer timer;
  timer.start();

  for (int y = 0; y < old_image_->height(); ++y) {
    const QRgb *old_line = (QRgb *)(old_image_->constScanLine(y));
    QRgb *target_line = (QRgb *)target_image_->scanLine(y);

    for (int x = 0; x < old_image_->width(); ++x) {
      target_line[x] = pixelOperation(x, y, old_line[x]);
    }
  }

  qDebug() << "The operation took" << timer.elapsed() << "milliseconds";
}

} // namespace imagecpp
