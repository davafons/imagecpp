#include "brightnesscontrast.hpp"

#include "image/document.hpp"

namespace imagecpp {

BrightnessAndConstrast::BrightnessAndConstrast(Document *document)
    : LutOperation(document, "Brightness/Contrast") {

  fillLutTables();
}

void BrightnessAndConstrast::setStd(float target_std) {
  float red_A = target_std / old_histogram()->red().standardDeviation();
  float green_A = target_std / old_histogram()->green().standardDeviation();
  float blue_A = target_std / old_histogram()->blue().standardDeviation();

  setA(red_A, green_A, blue_A);
}

void BrightnessAndConstrast::setMean(float target_mean) {
  float red_B = target_mean / old_histogram()->red().mean();
  float green_B = target_mean / old_histogram()->green().mean();
  float blue_B = target_mean / old_histogram()->blue().mean();

  setB(red_B, green_B, blue_B);
}

void BrightnessAndConstrast::setA(float A) { setA(A, A, A); }

void BrightnessAndConstrast::setA(float red_A, float green_A, float blue_A) {
  blockSignals(true);
  setRedA(red_A);
  setGreenA(green_A);
  setBlueA(blue_A);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float B) { setB(B, B, B); }

void BrightnessAndConstrast::setB(float red_B, float green_B, float blue_B) {
  blockSignals(true);
  setRedB(red_B);
  setGreenB(green_B);
  setBlueB(blue_B);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::setRedA(float A) {
  red_.A = A;

  emit propertyChanged();
}

void BrightnessAndConstrast::setRedB(float B) {
  red_.B = B;

  emit propertyChanged();
}

void BrightnessAndConstrast::setGreenA(float A) {
  green_.A = A;

  emit propertyChanged();
}

void BrightnessAndConstrast::setGreenB(float B) {
  green_.B = B;

  emit propertyChanged();
}

void BrightnessAndConstrast::setBlueA(float A) {
  blue_.A = A;

  emit propertyChanged();
}

void BrightnessAndConstrast::setBlueB(float B) {
  blue_.B = B;

  emit propertyChanged();
}

void BrightnessAndConstrast::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = std::max(0.0f, std::min(red_.A * i + red_.B, 255.0f));
    g_lut_[i] = std::max(0.0f, std::min(green_.A * i + green_.B, 255.0f));
    b_lut_[i] = std::max(0.0f, std::min(blue_.A * i + blue_.B, 255.0f));
  }
}

BACConfigDialog::BACConfigDialog(Document *document, QWidget *parent)
    : OperationConfigDialog(document, parent) {

  a_spin_.setRange(-127, 127);
  b_spin_.setRange(-127, 127);

  settings_layout_->addWidget(&a_spin_);
  settings_layout_->addWidget(&b_spin_);

  connect(&a_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, qOverload<float>(&BrightnessAndConstrast::setA));

  connect(&b_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, qOverload<float>(&BrightnessAndConstrast::setB));
}

} // namespace imagecpp
