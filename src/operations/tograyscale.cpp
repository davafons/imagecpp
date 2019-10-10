#include "tograyscale.hpp"

#include <QGroupBox>
#include <QRadioButton>

// --- Implementation ---

ToGrayscaleOperation::ToGrayscaleOperation(ImageData *data,
                                           const Format &format)
    : ImageOperation(data) {
  setFormat(format);
}

ToGrayscaleOperation &ToGrayscaleOperation::setFormat(const Format &format) {
  format_ = format;

  red_factor_ = (format_ == Format::PAL) ? 0.222f : 0.299f;
  green_factor_ = (format_ == Format::PAL) ? 0.707f : 0.587f;
  blue_factor_ = (format_ == Format::PAL) ? 0.071f : 0.114f;

  setName(QString("To Grayscale (%1)")
              .arg((format == Format::PAL) ? "PAL" : "NTSC"));

  emit propertyChanged();

  return *this;
}

QRgb ToGrayscaleOperation::pixelOperation(int, int, QRgb color) const {
  uint8_t red = qRed(color) * red_factor_;
  uint8_t green = qGreen(color) * green_factor_;
  uint8_t blue = qBlue(color) * blue_factor_;

  uint8_t gray = std::min(red + green + blue, 255);

  return qRgba(gray, gray, gray, qAlpha(color));
}

// --- Dialog ---

ToGrayscaleDialog::ToGrayscaleDialog(ImageData *data, QWidget *parent)
    : ImageOperationDialog(data, parent) {
  QGroupBox *group_box = new QGroupBox("Format");
  QVBoxLayout *vbox = new QVBoxLayout();

  pal_radio_ = new QRadioButton("PAL");
  ntsc_radio_ = new QRadioButton("NTSC");

  pal_radio_->setChecked(true);

  vbox->addWidget(pal_radio_);
  vbox->addWidget(ntsc_radio_);
  vbox->addSpacerItem(new QSpacerItem(200, 400));
  group_box->setLayout(vbox);

  settings_layout_->addWidget(group_box);

  connect(pal_radio_, &QRadioButton::toggled, &operation_,
          [this] { operation_.setFormat(ToGrayscaleOperation::Format::PAL); });

  connect(ntsc_radio_, &QRadioButton::toggled, &operation_,
          [this] { operation_.setFormat(ToGrayscaleOperation::Format::NTSC); });
}
