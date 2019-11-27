#pragma once

#include "operations/private/imageoperationdialog.hpp"
#include "rotation.hpp"

class QSpinBox;

namespace imagecpp {

class RotationDialog : public ImageOperationDialog<Rotation> {
public:
  explicit RotationDialog(Document *document, QWidget *parent = nullptr);

private:
  QSpinBox *degrees_spin_{nullptr};
};

}  // namespace imagecpp
