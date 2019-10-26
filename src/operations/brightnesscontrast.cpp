#include "brightnesscontrast.hpp"

#include <QFormLayout>
#include <QLabel>

#include "image/document.hpp"

namespace imagecpp {

/*!
 *  \class BrightnessAndContrast
 *  \brief Transforms the brightness or constrast of an image.
 */

/*!
 *  Construcs a BrightnessAndConstrast operation object.
 */
BrightnessAndConstrast::BrightnessAndConstrast(Document *document)
    : LutOperation(document, tr("Brightness/Contrast")) {}

/*!
 *  Sets the desired standard deviation (constrast) of the image.
 *
 *  \sa setA()
 */
void BrightnessAndConstrast::setStd(float target_std) {
  float red_A = target_std / oldHistogram()->red().standardDeviation();
  float green_A = target_std / oldHistogram()->green().standardDeviation();
  float blue_A = target_std / oldHistogram()->blue().standardDeviation();

  setA(red_A, green_A, blue_A);
}

void BrightnessAndConstrast::setMean(float target_mean) {
  float red_B = target_mean - red_.A * oldHistogram()->red().mean();
  float green_B = target_mean - green_.A * oldHistogram()->green().mean();
  float blue_B = target_mean - blue_.A * oldHistogram()->blue().mean();

  setB(red_B, green_B, blue_B);
}

void BrightnessAndConstrast::setA(float A, Channel channel) {
  switch (channel) {
    case Channel::Red:
      red_.A = A;
      break;

    case Channel::Green:
      green_.A = A;
      break;

    case Channel::Blue:
      blue_.A = A;
      break;

    default:
    case Channel::All:
      red_.A = A;
      green_.A = A;
      blue_.A = A;
      break;
  }

  emit propertyChanged();
}

void BrightnessAndConstrast::setA(float red_A, float green_A, float blue_A) {
  blockSignals(true);
  setA(red_A, Channel::Red);
  setA(green_A, Channel::Green);
  setA(blue_A, Channel::Blue);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float B, Channel channel) {
  switch (channel) {
    case Channel::Red:
      red_.B = B;
      break;

    case Channel::Green:
      green_.B = B;
      break;

    case Channel::Blue:
      blue_.B = B;
      break;

    default:
    case Channel::All:
      red_.B = B;
      green_.B = B;
      blue_.B = B;
      break;
  }

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float red_B, float green_B, float blue_B) {
  blockSignals(true);
  setB(red_B, Channel::Red);
  setB(green_B, Channel::Green);
  setB(blue_B, Channel::Blue);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::fillLutTablesImpl() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = std::max(0.0f, std::min(red_.A * i + red_.B, 255.0f));
    g_lut_[i] = std::max(0.0f, std::min(green_.A * i + green_.B, 255.0f));
    b_lut_[i] = std::max(0.0f, std::min(blue_.A * i + blue_.B, 255.0f));
  }
}

/*!
 *
 *
 *
 *
 *
 *
 */

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
  connect(&brightness_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_,
          &BrightnessAndConstrast::setMean);

  connect(&contrast_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_,
          &BrightnessAndConstrast::setStd);

  connect(&a_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_,
          qOverload<float>(&BrightnessAndConstrast::setA));

  connect(&b_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation_,
          qOverload<float>(&BrightnessAndConstrast::setB));
}

}  // namespace imagecpp
