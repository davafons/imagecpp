#include "rotationdialog.hpp"

#include <QFormLayout>
#include <QSpinBox>
#include <limits>

namespace imagecpp {

RotationDialog::RotationDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Rotation>(document, parent) {

  angle_spin_ = new QSpinBox();
  angle_spin_->setRange(std::numeric_limits<int>::min(),
                        std::numeric_limits<int>::max());

  QFormLayout *layout = new QFormLayout();

  layout->addRow(tr("Angle"), angle_spin_);

  settings_layout_->addLayout(layout);

  nn_radio_ = new QRadioButton("Nearest Neighbour");
  bilineal_radio_ = new QRadioButton("Bilineal");
  rotate_and_paint_radio_ = new QRadioButton("Rotate and Paint");

  switch (operation().interpolation()) {
    case Rotation::Interpolation::NN:
      nn_radio_->setChecked(true);
      break;

    case Rotation::Interpolation::Bilineal:
      bilineal_radio_->setChecked(true);
      break;

    case Rotation::Interpolation::RotateAndPaint:
      rotate_and_paint_radio_->setChecked(true);
      break;
  }

  QGroupBox *interpolation_group = new QGroupBox("Interpolation");
  QVBoxLayout *interpolation_group_layout = new QVBoxLayout();

  interpolation_group_layout->addWidget(nn_radio_);
  interpolation_group_layout->addWidget(bilineal_radio_);
  interpolation_group_layout->addWidget(rotate_and_paint_radio_);
  interpolation_group_layout->addSpacerItem(new QSpacerItem(200, 400));

  interpolation_group->setLayout(interpolation_group_layout);

  settings_layout_->addWidget(interpolation_group);

  // Connections

  connect(angle_spin_,
          QOverload<int>::of(&QSpinBox::valueChanged),
          &operation(),
          &Rotation::setAngle);

  connect(nn_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setInterpolation(Rotation::Interpolation::NN);
    }
  });

  connect(bilineal_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setInterpolation(Rotation::Interpolation::Bilineal);
    }
  });

  connect(rotate_and_paint_radio_, &QRadioButton::toggled, this, [this](bool checked) {
    if (checked) {
      operation().setInterpolation(Rotation::Interpolation::RotateAndPaint);
    }
  });
}

}  // namespace imagecpp
