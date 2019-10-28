#include "digitalizationdialog.hpp"

namespace imagecpp {

DigitalizationDialog::DigitalizationDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Digitalization>(document, parent) {

  sampling_spin_ = new QSpinBox();
  sampling_spin_->setRange(1, 100);  // TODO: Set actual max value
  sampling_spin_->setValue(operation().samplingSize());

  connect(sampling_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Digitalization::setSamplingSize);

  settings_layout_->addWidget(sampling_spin_);
}

}  // namespace imagecpp
