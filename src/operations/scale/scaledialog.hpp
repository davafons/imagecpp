#pragma once

#include <QCheckBox>

#include "operations/private/imageoperationdialog.hpp"
#include "scale.hpp"

class QDoubleSpinBox;

namespace imagecpp {

class Document;

class ScaleDialog : public ImageOperationDialog<Scale> {
  Q_OBJECT

public:
  explicit ScaleDialog(Document* document, QWidget* parent = nullptr);

private:
  QDoubleSpinBox* x_scale_spin_{nullptr};
  QDoubleSpinBox* y_scale_spin_{nullptr};

  QSpinBox* width_spin_{nullptr};
  QSpinBox* height_spin_{nullptr};

  QRadioButton* nn_radio_{nullptr};
  QRadioButton* bilineal_radio_{nullptr};

  QCheckBox* aspect_ratio_checkbox_{nullptr};
};
}  // namespace imagecpp
