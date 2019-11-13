#include "equalization.hpp"

namespace imagecpp {

/*!
 *  \class Equalization
 *  \brief Equalization of an image
 */

/*!
 *  Constructs an Equalization operation object.
 */
Equalization::Equalization(Document* document)
    : PointOperation(document, tr("Equalization")),
      M(oldImage()->width()),
      N(oldImage()->height()) {

  red_ch_ = oldHistogram().red().cummulativeBars();
  green_ch_ = oldHistogram().green().cummulativeBars();
  blue_ch_ = oldHistogram().blue().cummulativeBars();
}

/*!
 *  Implementation of the Equalization operation.
 */
QRgb Equalization::pointOperationImpl(int, int, QRgb color) {
  int red_ch_value = red_ch_->at(qRed(color));
  int green_ch_value = green_ch_->at(qGreen(color));
  int blue_ch_value = blue_ch_->at(qBlue(color));

  auto equalize = [this](int value) { return value * (K - 1) / (M * N); };

  return qRgb(
      equalize(red_ch_value), equalize(green_ch_value), equalize(blue_ch_value));
}

}  // namespace imagecpp
