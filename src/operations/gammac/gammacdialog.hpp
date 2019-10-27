#pragma once

#include "gammac.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class Document;

class GammaCorrectionDialog : public ImageOperationDialog<GammaCorrection> {
  Q_OBJECT

public:
  explicit GammaCorrectionDialog(Document *document, QWidget *parent = nullptr);
  virtual ~GammaCorrectionDialog() = default;

private:
  QDoubleSpinBox gamma_spin_;
};

}  // namespace imagecpp
