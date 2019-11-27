#include "bacdialog.hpp"

namespace imagecpp {

BACDialog::BACDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<BrightnessAndConstrast>(document, parent) {

  general_box_ = new QGroupBox();
  general_bright_slider_ = new SliderWithValues(Qt::Horizontal);
  general_contrast_slider_ = new SliderWithValues(Qt::Horizontal);

  rgb_bright_box_ = new QGroupBox();
  red_bright_slider_ = new SliderWithValues(Qt::Horizontal);
  green_bright_slider_ = new SliderWithValues(Qt::Horizontal);
  blue_bright_slider_ = new SliderWithValues(Qt::Horizontal);

  rgb_contrast_box_ = new QGroupBox();
  red_contrast_slider_ = new SliderWithValues(Qt::Horizontal);
  green_contrast_slider_ = new SliderWithValues(Qt::Horizontal);
  blue_contrast_slider_ = new SliderWithValues(Qt::Horizontal);

  resetSliders();

  // General box
  QFormLayout *general_layout = new QFormLayout();
  general_layout->addRow(tr("Brightness: "), general_bright_slider_);
  general_layout->addRow(tr("Contrast: "), general_contrast_slider_);

  general_box_->setTitle("General");
  general_box_->setLayout(general_layout);

  // -- Connect sliders

  connect(general_bright_slider_, &SliderWithValues::valueChanged, [this](int value) {
    operation().setMean(value);
  });

  connect(general_contrast_slider_, &SliderWithValues::valueChanged, [this](int value) {
    operation().setStd(value);
  });

  // Brightness box
  QFormLayout *rgb_bright_layout = new QFormLayout();
  rgb_bright_layout->addRow(tr("Red: "), red_bright_slider_);
  rgb_bright_layout->addRow(tr("Green: "), green_bright_slider_);
  rgb_bright_layout->addRow(tr("Blue: "), blue_bright_slider_);

  rgb_bright_box_->setTitle("Brightness");
  rgb_bright_box_->setLayout(rgb_bright_layout);
  rgb_bright_box_->setVisible(false);

  // -- Connect sliders
  connect(red_bright_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setMean(value, BrightnessAndConstrast::Channel::Red);
          });

  connect(green_bright_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setMean(value, BrightnessAndConstrast::Channel::Green);
          });

  connect(blue_bright_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setMean(value, BrightnessAndConstrast::Channel::Blue);
          });

  // Contrast box
  QFormLayout *rgb_constrast_layout = new QFormLayout();
  rgb_constrast_layout->addRow(tr("Red: "), red_contrast_slider_);
  rgb_constrast_layout->addRow(tr("Green: "), green_contrast_slider_);
  rgb_constrast_layout->addRow(tr("Blue: "), blue_contrast_slider_);

  rgb_contrast_box_->setTitle("Contrast");
  rgb_contrast_box_->setLayout(rgb_constrast_layout);
  rgb_contrast_box_->setVisible(false);

  // -- Connect sliders
  connect(red_contrast_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setStd(value, BrightnessAndConstrast::Channel::Red);
          });

  connect(green_contrast_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setStd(value, BrightnessAndConstrast::Channel::Green);
          });

  connect(blue_contrast_slider_,
          &SliderWithValues::valueChanged,
          &operation(),
          [this](int value) {
            operation().setStd(value, BrightnessAndConstrast::Channel::Blue);
          });

  // Buttons
  QHBoxLayout *buttons_layout = new QHBoxLayout();
  buttons_layout->addWidget(&reset_button_);
  buttons_layout->addWidget(&more_button_);

  more_button_.setCheckable(true);
  more_button_.setChecked(false);

  // -- Connect buttons
  connect(&reset_button_, &QPushButton::clicked, this, &BACDialog::resetSliders);
  connect(&more_button_, &QPushButton::clicked, this, [this](bool checked) {
    if (checked) {
      more_button_.setText(tr("Hide"));
    } else {
      more_button_.setText(tr("More"));
    }

    rgb_bright_box_->setVisible(checked);
    rgb_contrast_box_->setVisible(checked);
  });

  // Create final layout
  QVBoxLayout *boxes_layout = new QVBoxLayout();
  boxes_layout->addWidget(general_box_);
  boxes_layout->addWidget(rgb_bright_box_);
  boxes_layout->addWidget(rgb_contrast_box_);
  boxes_layout->addLayout(buttons_layout);

  settings_layout_->addLayout(boxes_layout);
}

void BACDialog::resetSliders() {
  // General sliders
  general_bright_slider_->setRange(0, 255);
  general_bright_slider_->setValue(operation().oldHistogram().mean());
  general_contrast_slider_->setRange(0, 255);
  general_contrast_slider_->setValue(operation().oldHistogram().stdev());

  // Brightness sliders
  red_bright_slider_->setRange(0, 255);
  red_bright_slider_->setValue(operation().oldHistogram().red().mean());
  green_bright_slider_->setRange(0, 255);
  green_bright_slider_->setValue(operation().oldHistogram().green().mean());
  blue_bright_slider_->setRange(0, 255);
  blue_bright_slider_->setValue(operation().oldHistogram().blue().mean());

  // Constrast sliders
  red_contrast_slider_->setRange(0, 255);
  red_contrast_slider_->setValue(operation().oldHistogram().red().stdev());
  green_contrast_slider_->setRange(0, 255);
  green_contrast_slider_->setValue(operation().oldHistogram().green().stdev());
  blue_contrast_slider_->setRange(0, 255);
  blue_contrast_slider_->setValue(operation().oldHistogram().blue().stdev());
}

}  // namespace imagecpp
