#include "operations/private/pixeloperation.hpp"

#include <QElapsedTimer>

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

/*!
 *  \class PixelOperation
 *  \brief Base class for image operations that act on each pixel.
 *
 *  All the subclasses must implement pixelOperationImpl, which as a result should
 *  decide the color for every input pixel.
 */

/*!
 *  Constructs the pixel operation. Document and name are properties needed for the
 *  parent constructor.
 */
PixelOperation::PixelOperation(Document *document, const QString &name)
    : ImageOperation(document, name) {}

/*!
 *  Iterates through each pixel of the old image, and sets the corresponding pixel on
 *  new_image to the resulting value of pixelOperationImpl.
 *
 *  TODO: Iterate only over the image selection
 */
void PixelOperation::imageOperationImpl(Image *new_image) {
  QElapsedTimer timer;
  timer.start();

  for (int y = 0; y < oldImage()->height(); ++y) {
    const QRgb *old_line = (QRgb *)(oldImage()->constScanLine(y));
    QRgb *new_line = (QRgb *)new_image->scanLine(y);

    for (int x = 0; x < oldImage()->width(); ++x) {
      new_line[x] = pixelOperationImpl(x, y, old_line[x]);
    }
  }

  qInfo() << "The operation took" << timer.elapsed() << "milliseconds";
}

}  // namespace imagecpp
