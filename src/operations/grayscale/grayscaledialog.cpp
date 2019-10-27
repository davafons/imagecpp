#include "grayscaledialog.hpp"

namespace imagecpp {
GrayscaleDialog::GrayscaleDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Grayscale>(document, parent) {

  pal_radio_ = new QRadioButton("PAL");
  ntsc_radio_ = new QRadioButton("NTSC");

  if (operation().format() == Grayscale::Format::PAL) {
    pal_radio_->setChecked(true);
  } else {
    ntsc_radio_->setChecked(true);
  }

  QGroupBox *formats_box = new QGroupBox("Format");
  QVBoxLayout *formats_layout = new QVBoxLayout();

  formats_layout->addWidget(pal_radio_);
  formats_layout->addWidget(ntsc_radio_);
  formats_layout->addSpacerItem(new QSpacerItem(200, 400));
  formats_box->setLayout(formats_layout);

  settings_layout_->addWidget(formats_box);

  // Connections
  connect(pal_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setFormat(Grayscale::Format::PAL);
    }
  });

  connect(ntsc_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setFormat(Grayscale::Format::NTSC);
    }
  });
}

}  // namespace imagecpp
