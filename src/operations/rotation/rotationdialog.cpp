#include "rotationdialog.hpp"

#include <QFormLayout>
#include <QSpinBox>
#include <limits>

namespace imagecpp {

RotationDialog::RotationDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Rotation>(document, parent) {

  degrees_spin_ = new QSpinBox();
  degrees_spin_->setRange(std::numeric_limits<int>::min(),
                          std::numeric_limits<int>::max());

  QFormLayout *layout = new QFormLayout();

  layout->addRow(tr("Degrees"), degrees_spin_);

  settings_layout_->addLayout(layout);

  // Connections

  connect(degrees_spin_,
          QOverload<int>::of(&QSpinBox::valueChanged),
          &operation(),
          &Rotation::setDegrees);
}

}  // namespace imagecpp
