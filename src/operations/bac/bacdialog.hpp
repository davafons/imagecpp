#pragma once

#include "bac.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class Document;

class BACDialog : public ImageOperationDialog<BrightnessAndConstrast> {
  Q_OBJECT

public:
  explicit BACDialog(Document *document, QWidget *parent = nullptr);
  virtual ~BACDialog() = default;

private slots:
  void resetSliders();

private:
  QGroupBox general_box_;
  QSlider general_bright_slider_{Qt::Horizontal};
  QSlider general_contrast_slider_{Qt::Horizontal};

  QGroupBox rgb_bright_box_;
  QSlider red_bright_slider_{Qt::Horizontal};
  QSlider green_bright_slider_{Qt::Horizontal};
  QSlider blue_bright_slider_{Qt::Horizontal};

  QGroupBox rgb_contrast_box_;
  QSlider red_contrast_slider_{Qt::Horizontal};
  QSlider green_contrast_slider_{Qt::Horizontal};
  QSlider blue_contrast_slider_{Qt::Horizontal};

  QPushButton reset_button_{tr("Reset")};
  QPushButton more_button_{tr("More")};
};

}  // namespace imagecpp
