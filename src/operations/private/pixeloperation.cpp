#include "operations/private/pixeloperation.hpp"

#include <QElapsedTimer>

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

PixelOperation::PixelOperation(Document *document, const QString &name)
    : ImageOperation(document, name) {}

void PixelOperation::applyImageOperation() {
  QElapsedTimer timer;
  timer.start();

  for (int y = 0; y < old_image_->height(); ++y) {
    const QRgb *old_line = (QRgb *)(old_image_->constScanLine(y));
    QRgb *target_line = (QRgb *)target_image_->scanLine(y);

    for (int x = 0; x < old_image_->width(); ++x) {
      // if (selection().contains(x, y)) {
      target_line[x] = pixelOperation(x, y, old_line[x]);
      // } else {
      //   target_line[x] = old_line[x];
      // }
    }
  }

  qDebug() << "The operation took" << timer.elapsed() << "milliseconds";
}

} // namespace imagecpp
