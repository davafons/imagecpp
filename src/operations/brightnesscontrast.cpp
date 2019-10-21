#include "brightnesscontrast.hpp"

#include <QFormLayout>
#include <QLabel>

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

  qDebug() << "Desired std" << target_std;

  qDebug() << "A: Red std from" << old_histogram()->red().standardDeviation()
           << "to" << red_A;

  qDebug() << "A: Green std from"
           << old_histogram()->green().standardDeviation() << "to" << green_A;

  qDebug() << "A: Blue std from" << old_histogram()->blue().standardDeviation()
           << "to" << blue_A;

  setA(red_A, green_A, blue_A);
}

void BrightnessAndConstrast::setMean(float target_mean) {
  float red_B = target_mean - red_.A * old_histogram()->red().mean();
  float green_B = target_mean - green_.A * old_histogram()->green().mean();
  float blue_B = target_mean - blue_.A * old_histogram()->blue().mean();

  qDebug() << "Desired mean" << target_mean;

  qDebug() << "B: Red mean from" << old_histogram()->red().mean() << "to"
           << red_B;

  qDebug() << "B: Green mean from" << old_histogram()->green().mean() << "to"
           << green_B;

  qDebug() << "B: Blue mean from" << old_histogram()->blue().mean() << "to"
           << blue_B;

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

  // Configure widgets
  brightness_spin_.setRange(-255, 255);
  contrast_spin_.setRange(0, 255);

  // a_spin_.setRange(-127, 127);
  // b_spin_.setRange(-127, 127);
  //
  // settings_layout_->addWidget(&a_spin_);
  // settings_layout_->addWidget(&b_spin_);

  // Setup layout

  QFormLayout *basic_parameters_layout = new QFormLayout();

  basic_parameters_layout->addRow(tr("Brightness:"), &brightness_spin_);
  basic_parameters_layout->addRow(tr("Contrast:"), &contrast_spin_);

  settings_layout_->addLayout(basic_parameters_layout);

  // Add connections
  connect(&brightness_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, &BrightnessAndConstrast::setMean);

  connect(&contrast_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, &BrightnessAndConstrast::setStd);

  connect(&a_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, qOverload<float>(&BrightnessAndConstrast::setA));

  connect(&b_spin_, qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_, qOverload<float>(&BrightnessAndConstrast::setB));
}

} // namespace imagecpp
