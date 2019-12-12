#include "scaledialog.hpp"

#include <QSpinBox>

namespace imagecpp {

ScaleDialog::ScaleDialog(Document* document, QWidget* parent)
    : ImageOperationDialog<Scale>(document, parent) {

  x_scale_spin_ = new QSpinBox();
  y_scale_spin_ = new QSpinBox();

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

  settings_layout_->addWidget(x_scale_spin_);
  settings_layout_->addWidget(y_scale_spin_);
  settings_layout_->addWidget(interpolation_group);

  // TODO: Add desired size also

  // connect(&operation(), &ImageOperation::propertyChanged, this, [this]() {
  //   qDebug() << "Fit on frame";
  //   preview_display_->fitOnFrame();
  // });

  connect(x_scale_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleX);

  connect(y_scale_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &Scale::setScaleY);

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
