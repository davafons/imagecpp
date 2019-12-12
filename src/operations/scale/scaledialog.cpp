#include "scaledialog.hpp"

#include <QDoubleSpinBox>

namespace imagecpp {

ScaleDialog::ScaleDialog(Document* document, QWidget* parent)
    : ImageOperationDialog<Scale>(document, parent) {

  QFormLayout* form_layout = new QFormLayout();

  x_scale_spin_ = new QDoubleSpinBox();
  y_scale_spin_ = new QDoubleSpinBox();

  width_spin_ = new QSpinBox();
  height_spin_ = new QSpinBox();

  nn_radio_ = new QRadioButton("Nearest Neighbour");
  bilineal_radio_ = new QRadioButton("Bilineal");

  if (operation().interpolation() == Scale::Interpolation::NN) {
    nn_radio_->setChecked(true);
  } else {
    bilineal_radio_->setChecked(true);
  }

  QGroupBox* interpolation_group = new QGroupBox("Interpolation");
  QVBoxLayout* interpolation_group_layout = new QVBoxLayout();

  interpolation_group_layout->addWidget(nn_radio_);
  interpolation_group_layout->addWidget(bilineal_radio_);
  interpolation_group_layout->addSpacerItem(new QSpacerItem(200, 400));

  interpolation_group->setLayout(interpolation_group_layout);

  x_scale_spin_->setRange(1, 1000);
  y_scale_spin_->setRange(1, 1000);
  x_scale_spin_->setValue(operation().scaleX());
  y_scale_spin_->setValue(operation().scaleY());

  width_spin_->setRange(1, 100000000);
  height_spin_->setRange(1, 100000000);
  width_spin_->setValue(operation().newImage()->width());
  height_spin_->setValue(operation().newImage()->height());

  form_layout->addRow("Scale X:", x_scale_spin_);
  form_layout->addRow("Scale Y:", y_scale_spin_);

  form_layout->addRow("Width: ", width_spin_);
  form_layout->addRow("Height: ", height_spin_);

  form_layout->addWidget(interpolation_group);

  settings_layout_->addLayout(form_layout);

  // TODO: Add desired size also

  connect(&operation(), &ImageOperation::propertyChanged, this, [this]() {
    x_scale_spin_->blockSignals(true);
    x_scale_spin_->setValue(operation().scaleX());
    x_scale_spin_->blockSignals(false);

    y_scale_spin_->blockSignals(true);
    y_scale_spin_->setValue(operation().scaleY());
    y_scale_spin_->blockSignals(false);

    width_spin_->blockSignals(true);
    width_spin_->setValue(operation().oldImage()->width() * operation().scaleX() / 100);
    width_spin_->blockSignals(false);

    height_spin_->blockSignals(true);
    height_spin_->setValue(operation().oldImage()->height() * operation().scaleY() / 100);
    height_spin_->blockSignals(false);
  });

  connect(x_scale_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleX);

  connect(y_scale_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleY);

  connect(width_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setWidth);

  connect(height_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setHeight);

  connect(nn_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setInterpolation(Scale::Interpolation::NN);
    }
  });

  connect(bilineal_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setInterpolation(Scale::Interpolation::Bilineal);
    }
  });
}

}  // namespace imagecpp
