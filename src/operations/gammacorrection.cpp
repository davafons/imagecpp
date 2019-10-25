#include "gammacorrection.hpp"

#include <cmath>

namespace imagecpp {
GammaCorrection::GammaCorrection(Document *document)
    : LutOperation(document, "Gamma Correction") {
  fillLutTables();
}

void GammaCorrection::setGamma(float gamma) {
  gamma_ = gamma;

  emit propertyChanged();

  // return *this;
}

void GammaCorrection::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    float a = float(i) / LUT_SIZE;
    float b = std::pow(a, gamma_);
    int vout = b * LUT_SIZE;

    r_lut_[i] = vout;
    g_lut_[i] = vout;
    b_lut_[i] = vout;

    qDebug() << i << "-" << r_lut_[i];
  }
}

// --- Dialog ---

GammaCorrectionConfigDialog::GammaCorrectionConfigDialog(Document *document,
                                                         QWidget *parent)
    : OperationConfigDialog(document, parent) {
  settings_layout_->addWidget(&gamma_spin_);

  gamma_spin_.setValue(1.0f);
  gamma_spin_.setSingleStep(0.1f);

  connect(&gamma_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, &GammaCorrection::setGamma);
}

} // namespace imagecpp
