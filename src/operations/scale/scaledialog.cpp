#include "scaledialog.hpp"

#include <QDoubleSpinBox>
#include <numeric>

namespace imagecpp {

ScaleDialog::ScaleDialog(Document* document, QWidget* parent)
    : ImageOperationDialog<Scale>(document, parent) {

  QFormLayout* form_layout = new QFormLayout();

  aspect_ratio_checkbox_ = new QCheckBox("Keep Aspect Ratio");
  aspect_ratio_checkbox_->setChecked(operation().aspectRatioToggled());

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

  interpolation_group->setLayout(interpolation_group_layout);

  x_scale_spin_->setRange(1, std::numeric_limits<int>::max());
  y_scale_spin_->setRange(1, std::numeric_limits<int>::max());
  x_scale_spin_->setValue(operation().scaleX());
  y_scale_spin_->setValue(operation().scaleY());

  width_spin_->setRange(1, std::numeric_limits<int>::max());
  height_spin_->setRange(1, std::numeric_limits<int>::max());
  width_spin_->setValue(operation().newImage()->width());
  height_spin_->setValue(operation().newImage()->height());

  form_layout->addRow("Scale X:", x_scale_spin_);
  form_layout->addRow("Scale Y:", y_scale_spin_);

  form_layout->addRow("Width: ", width_spin_);
  form_layout->addRow("Height: ", height_spin_);

  settings_layout_->addLayout(form_layout);
  settings_layout_->addWidget(interpolation_group);
  settings_layout_->addWidget(aspect_ratio_checkbox_);
  settings_layout_->addWidget(new QLabel(tr("Initial Dimensions: %1 x %2")
                                             .arg(operation().oldImage()->width())
                                             .arg(operation().oldImage()->height())));

  settings_layout_->addSpacerItem(new QSpacerItem(200, 400));

  connect(x_scale_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          this,
          [this](double value) {
            operation().setScaleX(value);

            if (operation().aspectRatioToggled()) {
              y_scale_spin_->setValue(value);
            }

            width_spin_->blockSignals(true);
            width_spin_->setValue(operation().newWidth());
            width_spin_->blockSignals(false);
          });

  connect(y_scale_spin_,
          qOverload<double>(&QDoubleSpinBox::valueChanged),
          this,
          [this](double value) {
            operation().setScaleY(value);

            if (operation().aspectRatioToggled()) {
              x_scale_spin_->setValue(value);
            }

            height_spin_->blockSignals(true);
            height_spin_->setValue(operation().newHeight());
            height_spin_->blockSignals(false);
          });

  connect(
      width_spin_, qOverload<int>(&QSpinBox::valueChanged), this, [this](int width) {
        operation().setWidth(width);

        if (operation().aspectRatioToggled()) {
          operation().setHeight(width * operation().aspectRatio());

          y_scale_spin_->blockSignals(true);
          y_scale_spin_->setValue(width * operation().aspectRatio());
          y_scale_spin_->blockSignals(false);

          height_spin_->blockSignals(true);
          height_spin_->setValue(operation().newHeight());
          height_spin_->blockSignals(false);
        }

        x_scale_spin_->blockSignals(true);
        x_scale_spin_->setValue(operation().scaleX());
        x_scale_spin_->blockSignals(false);
      });

  connect(aspect_ratio_checkbox_,
          &QCheckBox::stateChanged,
          &operation(),
          &Scale::toggleKeepAspectRatio);

  connect(
      height_spin_, qOverload<int>(&QSpinBox::valueChanged), this, [this](int height) {
        operation().setHeight(height);

        if (operation().aspectRatioToggled()) {
          operation().setWidth(height / operation().aspectRatio());

          x_scale_spin_->blockSignals(true);
          x_scale_spin_->setValue(height / operation().aspectRatio());
          x_scale_spin_->blockSignals(false);

          width_spin_->blockSignals(true);
          width_spin_->setValue(operation().newWidth());
          width_spin_->blockSignals(false);
        }

        y_scale_spin_->blockSignals(true);
        y_scale_spin_->setValue(operation().scaleY());
        y_scale_spin_->blockSignals(false);
      });

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
