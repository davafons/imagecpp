#pragma once

#include "operations/private/imageoperationdialog.hpp"
#include "scale.hpp"

class QSpinBox;

namespace imagecpp {

class Document;

class ScaleDialog : public ImageOperationDialog<Scale> {
  Q_OBJECT

public:
  explicit ScaleDialog(Document* document, QWidget* parent = nullptr);

private:
  QSpinBox* x_scale_spin_{nullptr};
  QSpinBox* y_scale_spin_{nullptr};
};
}  // namespace imagecpp
