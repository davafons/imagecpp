#pragma once

#include "operations/private/imageoperationdialog.hpp"
#include "specification.hpp"

class QSpinBox;

namespace imagecpp {

class ImagesListWidget;
class ImageDisplayArea;

class SpecificationDialog: public ImageOperationDialog<Specification> {
  Q_OBJECT

public:
  explicit SpecificationDialog(Document *document, QWidget *parent = nullptr);

private:
  ImagesListWidget *images_list_widget_{nullptr};
  ImageDisplayArea *image_display_area_{nullptr};
};

}  // namespace imagecpp
