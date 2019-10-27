#include "gammacdialog.hpp"

namespace imagecpp {

GammaCorrectionDialog::GammaCorrectionDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<GammaCorrection>(document, parent) {

  settings_layout_->addWidget(&gamma_spin_);

  gamma_spin_.setValue(1.0f);
  gamma_spin_.setSingleStep(0.1f);

  connect(&gamma_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation(),
          &GammaCorrection::setGamma);
}

}  // namespace imagecpp
