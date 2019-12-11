#include "scaledialog.hpp"

#include <QSpinBox>

namespace imagecpp {

ScaleDialog::ScaleDialog(Document* document, QWidget* parent)
    : ImageOperationDialog<Scale>(document, parent) {

  x_scale_spin_ = new QSpinBox();
  y_scale_spin_ = new QSpinBox();

  x_scale_spin_->setMaximum(1000);
  y_scale_spin_->setMaximum(1000);

  x_scale_spin_->setValue(operation().scaleX());
  y_scale_spin_->setValue(operation().scaleY());

  settings_layout_->addWidget(x_scale_spin_);
  settings_layout_->addWidget(y_scale_spin_);

  // TODO: Add desired size also

  connect(x_scale_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleX);

  connect(y_scale_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleY);
}

}  // namespace imagecpp
