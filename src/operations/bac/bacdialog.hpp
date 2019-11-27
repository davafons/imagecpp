#pragma once

#include "bac.hpp"
#include "operations/private/imageoperationdialog.hpp"
#include "widgets/utils/sliderwithvalues.hpp"

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
  QGroupBox *general_box_{nullptr};
  SliderWithValues *general_bright_slider_{nullptr};
  SliderWithValues *general_contrast_slider_{nullptr};

  QGroupBox *rgb_bright_box_{nullptr};
  SliderWithValues *red_bright_slider_{nullptr};
  SliderWithValues *green_bright_slider_{nullptr};
  SliderWithValues *blue_bright_slider_{nullptr};

  QGroupBox *rgb_contrast_box_{nullptr};
  SliderWithValues *red_contrast_slider_{nullptr};
  SliderWithValues *green_contrast_slider_{nullptr};
  SliderWithValues *blue_contrast_slider_{nullptr};

  QPushButton reset_button_{tr("Reset")};
  QPushButton more_button_{tr("More")};
};

}  // namespace imagecpp
