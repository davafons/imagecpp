#pragma once

#include "digitalization.hpp"
#include "operations/private/imageoperationdialog.hpp"

class QSpinBox;

namespace imagecpp {

class DigitalizationDialog : public ImageOperationDialog<Digitalization> {
  Q_OBJECT

public:
  explicit DigitalizationDialog(Document *document, QWidget *parent = nullptr);
  virtual ~DigitalizationDialog() = default;

private:
  QSpinBox *sampling_spin_;
};

}  // namespace imagecpp
