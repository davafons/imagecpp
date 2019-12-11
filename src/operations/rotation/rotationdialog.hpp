#pragma once

#include "operations/private/imageoperationdialog.hpp"
#include "rotation.hpp"

class QSpinBox;

namespace imagecpp {

class RotationDialog : public ImageOperationDialog<Rotation> {
public:
  explicit RotationDialog(Document *document, QWidget *parent = nullptr);

private:
  QSpinBox *angle_spin_{nullptr};


  QRadioButton* nn_radio_{nullptr};
  QRadioButton* bilineal_radio_{nullptr};
};

}  // namespace imagecpp
