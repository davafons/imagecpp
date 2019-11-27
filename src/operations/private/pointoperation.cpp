#include "operations/private/pointoperation.hpp"

#include <QElapsedTimer>

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

/*!
 *  \class PointOperation
 *  \brief Base class for image operations that act on each pixel.
 *
 *  All the subclasses must implement pointOperationImpl, which as a result should
 *  decide the color for every input pixel.
 */

/*!
 *  Constructs the pixel operation. Document and name are properties needed for the
 *  parent constructor.
 */
PointOperation::PointOperation(Document *document, const QString &name)
    : ImageOperation(document, name) {}

/*!
 *  Iterates through each pixel of the old image, and sets the corresponding pixel on
 *  new_image to the resulting value of pointOperationImpl.
 *
 *  TODO: Iterate only over the image selection
 */
void PointOperation::imageOperationImpl(Image *new_image) {
  for (int y = 0; y < oldImage()->height(); ++y) {
    const QRgb *old_line = (QRgb *)(oldImage()->constScanLine(y));
    QRgb *new_line = (QRgb *)new_image->scanLine(y);

    for (int x = 0; x < oldImage()->width(); ++x) {
      if (selection().contains(x, y)) {
        new_line[x] = pointOperationImpl(x, y, old_line[x]);
      } else {
        new_line[x] = old_line[x];
      }
    }
  }
}

}  // namespace imagecpp
