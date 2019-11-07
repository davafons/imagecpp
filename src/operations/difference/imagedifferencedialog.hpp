#pragma once

#include "imagedifference.hpp"
#include "operations/private/imageoperationdialog.hpp"

class QSpinBox;

namespace imagecpp {

class ImagesListWidget;
class ImageDisplayArea;

class ImageDifferenceDialog : public ImageOperationDialog<ImageDifference> {
  Q_OBJECT

public:
  explicit ImageDifferenceDialog(Document *document, QWidget *parent = nullptr);

private:
  ImagesListWidget *images_list_widget_{nullptr};

  // ImageDisplayArea *image_display_area_{nullptr};

  QSpinBox *threshold_spin_{nullptr};

  QPushButton *color_picker_button_{nullptr};
};

}  // namespace imagecpp
