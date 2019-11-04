#include "digitalizationdialog.hpp"

#include <QFormLayout>

namespace imagecpp {

DigitalizationDialog::DigitalizationDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Digitalization>(document, parent) {

  QFormLayout *form_layout = new QFormLayout();

  sampling_spin_ = new QSpinBox();
  sampling_spin_->setRange(1, 100);  // TODO: Set actual max value
  sampling_spin_->setValue(operation().samplingSize());

  quantization_spin_ = new QSpinBox();
  quantization_spin_->setRange(1, 8);
  quantization_spin_->setValue(operation().quantizationFactor());

  connect(sampling_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Digitalization::setSamplingSize);

  connect(quantization_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Digitalization::setQuantizationFactor);

  form_layout->addRow(tr("Sampling size"), sampling_spin_);
  form_layout->addRow(tr("Quantization"), quantization_spin_);

  settings_layout_->addLayout(form_layout);
}

}  // namespace imagecpp
