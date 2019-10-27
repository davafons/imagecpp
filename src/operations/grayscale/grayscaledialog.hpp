#pragma once

#include "grayscale.hpp"
#include "operations/private/imageoperationdialog.hpp"

class QRadioButton;

namespace imagecpp {

class Document;

class GrayscaleDialog : public ImageOperationDialog<Grayscale> {
  Q_OBJECT

public:
  explicit GrayscaleDialog(Document *document, QWidget *parent = nullptr);

private:
  QRadioButton *pal_radio_{nullptr};
  QRadioButton *ntsc_radio_{nullptr};
};

}  // namespace imagecpp
