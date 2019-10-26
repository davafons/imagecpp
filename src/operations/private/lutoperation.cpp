#include "operations/private/lutoperation.hpp"

namespace imagecpp {

/*!
 *  \class LutOperation
 *  \brief Base class for image operations that implement a lut table.
 *
 *  A "Look-Up-Table" (lut table for short) are helper structures for pixel-wise
 *  operations. Instead of running the operation for each pixel, a lut table is
 *  calculated beforehand, storing the expected output color (Vout) for each input
 *  color (Vin). Thus, every lut operation must fill three arrays of 256 elements,
 *  each one corresponding to one RGB channel.
 *
 *  So, if the Vin is used as an index for the lut table, the corresponding Vout will
 *  be returned, saving lots of calculations.
 */

/*!
 *  Constructs the lut operation. Document and name properties are neccessary for the
 *  parent constructor.
 */
LutOperation::LutOperation(Document *document, const QString &name)
    : PixelOperation(document, name) {
  r_lut_.fill(0);
  g_lut_.fill(0);
  b_lut_.fill(0);
}
/*!
 *  Adds an extra step to the imageOperationImpl method: The fillLutTables method must
 *  be called first.
 */
void LutOperation::imageOperationImpl(Image *new_image) {
  fillLutTablesImpl();

  PixelOperation::imageOperationImpl(new_image);
}

/*!
 * Uses each component of the RGB color as an index of the lut table. The resulting
 * values will form the Vout RGB color.
 *
 * Note: Alpha channel will be left as is.
 */
QRgb LutOperation::pixelOperationImpl(int x, int y, QRgb color) const {
  return qRgba(
      r_lut_[qRed(color)], g_lut_[qGreen(color)], b_lut_[qBlue(color)], qAlpha(color));
}

}  // namespace imagecpp
