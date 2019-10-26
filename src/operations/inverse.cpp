#include "inverse.hpp"

#include "image/document.hpp"

namespace imagecpp {

/*!
 *  \class Inverse
 *  \brief Transforms an image to its inverse (swap colors);
 */

/*!
 *  Construcs an Inverse operation object.
 */
Inverse::Inverse(Document *document) : LutOperation(document, tr("Inverse")) {}

/*!
 *  Implementation of the Inverse operation.
 *
 *  Each entry will be transformed to the inverse of its intensity:
 *    * 0 -> 255
 *    * 1 -> 254
 *    * 2 -> 253
 *    * ...
 */
void Inverse::fillLutTablesImpl() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    int vout = LUT_SIZE - 1 - i;
    r_lut_[i] = vout;
    g_lut_[i] = vout;
    b_lut_[i] = vout;
  }
}

}  // namespace imagecpp
