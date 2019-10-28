#include "gammac.hpp"

#include <cmath>

namespace imagecpp {
/*!
 *  \class GammaCorrection
 *  \brief Applies a gamma correction an the image.
 */

/*!
 *  Construcs a GammaCorrection operation object.
 */
GammaCorrection::GammaCorrection(Document *document)
    : LutOperation(document, tr("Gamma Correction")) {}

/*!
 *  Returns the gamma factor used.
 */
float GammaCorrection::gamma() const {
  return gamma_;
}

/*!
 *  Sets a new gamma factor for the operation.
 */
void GammaCorrection::setGamma(float gamma) {
  gamma_ = gamma;

  emit propertyChanged();

  // return *this;
}

/*!
 *  Implementation of the GammaCorrection operation.
 *
 *  For every Vin:
 *    * Normalize its value to the (0..1) range (a)
 *    * Apply the gamma formula (b)
 *    * Return the value to the previous range (vout)
 */
void GammaCorrection::fillLutTablesImpl() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    float a = float(i) / LUT_SIZE;
    float b = std::pow(a, gamma_);
    int vout = b * LUT_SIZE;

    r_lut_[i] = vout;
    g_lut_[i] = vout;
    b_lut_[i] = vout;
  }
}

}  // namespace imagecpp
