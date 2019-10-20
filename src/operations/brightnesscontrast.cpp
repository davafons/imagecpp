#include "brightnesscontrast.hpp"

#include "image/document.hpp"

namespace imagecpp {

BrightnessAndConstrast::BrightnessAndConstrast(Document *document)
    : LutOperation(document, "Brightness/Contrast") {

  A_ = 1;
  B_ = 0;

  fillLutTables();
}

void BrightnessAndConstrast::setA(float A) {
  A_ = A;

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float B) {
  B_ = B;

  emit propertyChanged();
}

void BrightnessAndConstrast::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    int value = std::max(0.0f, std::min(A_ * i + B_, 255.0f));
    r_lut_[i] = value;
    g_lut_[i] = value;
    b_lut_[i] = value;
  }
}

BACConfigDialog::BACConfigDialog(Document *document, QWidget *parent)
    : OperationConfigDialog(document, parent) {

  a_spin_.setRange(-127, 127);
  b_spin_.setRange(-127, 127);

  settings_layout_->addWidget(&a_spin_);
  settings_layout_->addWidget(&b_spin_);

  connect(&a_spin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          &operation_, &BrightnessAndConstrast::setA);

  connect(&b_spin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          &operation_, &BrightnessAndConstrast::setB);
}

} // namespace imagecpp
