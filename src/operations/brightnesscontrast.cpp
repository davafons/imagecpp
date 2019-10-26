#include "brightnesscontrast.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>

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
void BrightnessAndConstrast::setStd(float desired_std, Channel channel) {
  float red_A = desired_std / oldHistogram()->red().stdev();
  float green_A = desired_std / oldHistogram()->green().stdev();
  float blue_A = desired_std / oldHistogram()->blue().stdev();

  switch (channel) {
    case Channel::Red:
      setA(red_A, channel);
      break;

    case Channel::Green:
      setA(green_A, channel);
      break;

    case Channel::Blue:
      setA(blue_A, channel);
      break;

    default:
    case Channel::All:
      setA(red_A, green_A, blue_A);
      break;
  }
}

void BrightnessAndConstrast::setMean(float desired_mean, Channel channel) {
  float red_B = desired_mean - red_.A * oldHistogram()->red().mean();
  float green_B = desired_mean - green_.A * oldHistogram()->green().mean();
  float blue_B = desired_mean - blue_.A * oldHistogram()->blue().mean();

  qDebug() << red_B;

  switch (channel) {
    case Channel::Red:
      setB(red_B, channel);
      break;

    case Channel::Green:
      setB(green_B, channel);
      break;

    case Channel::Blue:
      setB(blue_B, channel);
      break;

    default:
    case Channel::All:
      setB(red_B, green_B, blue_B);
      break;
  }
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

  resetSliders();

  // General box
  QFormLayout *general_layout = new QFormLayout();
  general_layout->addRow(tr("Brightness: "), &general_bright_slider_);
  general_layout->addRow(tr("Contrast: "), &general_contrast_slider_);

  general_box_.setTitle("General");
  general_box_.setLayout(general_layout);

  // -- Connect sliders

  connect(&general_bright_slider_, &QSlider::valueChanged, [this](int value) {
    operation_.setMean(value);
  });

  connect(&general_contrast_slider_, &QSlider::valueChanged, [this](int value) {
    operation_.setStd(value);
  });

  // Brightness box
  QFormLayout *rgb_bright_layout = new QFormLayout();
  rgb_bright_layout->addRow(tr("Red: "), &red_bright_slider_);
  rgb_bright_layout->addRow(tr("Green: "), &green_bright_slider_);
  rgb_bright_layout->addRow(tr("Blue: "), &blue_bright_slider_);

  rgb_bright_box_.setTitle("Brightness");
  rgb_bright_box_.setLayout(rgb_bright_layout);
  rgb_bright_box_.setVisible(false);

  // -- Connect sliders
  connect(&red_bright_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
    operation_.setMean(value, BrightnessAndConstrast::Channel::Red);
  });

  connect(
      &green_bright_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
        operation_.setMean(value, BrightnessAndConstrast::Channel::Green);
      });

  connect(&blue_bright_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
    operation_.setMean(value, BrightnessAndConstrast::Channel::Blue);
  });

  // Contrast box
  QFormLayout *rgb_constrast_layout = new QFormLayout();
  rgb_constrast_layout->addRow(tr("Red: "), &red_contrast_slider_);
  rgb_constrast_layout->addRow(tr("Green: "), &green_contrast_slider_);
  rgb_constrast_layout->addRow(tr("Blue: "), &blue_contrast_slider_);

  rgb_contrast_box_.setTitle("Contrast");
  rgb_contrast_box_.setLayout(rgb_constrast_layout);
  rgb_contrast_box_.setVisible(false);

  // -- Connect sliders
  connect(
      &red_contrast_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
        operation_.setStd(value, BrightnessAndConstrast::Channel::Red);
      });

  connect(
      &green_contrast_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
        operation_.setStd(value, BrightnessAndConstrast::Channel::Green);
      });

  connect(
      &blue_contrast_slider_, &QSlider::valueChanged, &operation_, [this](int value) {
        operation_.setStd(value, BrightnessAndConstrast::Channel::Blue);
      });

  // Buttons
  QHBoxLayout *buttons_layout = new QHBoxLayout();
  buttons_layout->addWidget(&reset_button_);
  buttons_layout->addWidget(&more_button_);

  more_button_.setCheckable(true);
  more_button_.setChecked(false);

  // -- Connect buttons
  connect(&reset_button_, &QPushButton::clicked, this, &BACConfigDialog::resetSliders);
  connect(&more_button_, &QPushButton::clicked, this, [this](bool checked) {
    if (checked) {
      more_button_.setText(tr("Hide"));
    } else {
      more_button_.setText(tr("More"));
    }

    rgb_bright_box_.setVisible(checked);
    rgb_contrast_box_.setVisible(checked);
  });

  // Create final layout
  QVBoxLayout *boxes_layout = new QVBoxLayout();
  boxes_layout->addWidget(&general_box_);
  boxes_layout->addWidget(&rgb_bright_box_);
  boxes_layout->addWidget(&rgb_contrast_box_);
  boxes_layout->addLayout(buttons_layout);

  settings_layout_->addLayout(boxes_layout);
}

void BACConfigDialog::resetSliders() {
  // General sliders
  general_bright_slider_.setRange(0, 255);
  general_bright_slider_.setValue(operation_.oldHistogram()->mean());
  general_contrast_slider_.setRange(0, 255);
  general_contrast_slider_.setValue(operation_.oldHistogram()->stdev());

  // Brightness sliders
  red_bright_slider_.setRange(0, 255);
  red_bright_slider_.setValue(operation_.oldHistogram()->red().mean());
  green_bright_slider_.setRange(0, 255);
  green_bright_slider_.setValue(operation_.oldHistogram()->green().mean());
  blue_bright_slider_.setRange(0, 255);
  blue_bright_slider_.setValue(operation_.oldHistogram()->blue().mean());

  // Constrast sliders
  red_contrast_slider_.setRange(0, 255);
  red_contrast_slider_.setValue(operation_.oldHistogram()->red().stdev());
  green_contrast_slider_.setRange(0, 255);
  green_contrast_slider_.setValue(operation_.oldHistogram()->green().stdev());
  blue_contrast_slider_.setRange(0, 255);
  blue_contrast_slider_.setValue(operation_.oldHistogram()->blue().stdev());
}

}  // namespace imagecpp
