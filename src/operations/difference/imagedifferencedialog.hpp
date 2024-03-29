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

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;

private:
  ImagesListWidget *images_list_widget_{nullptr};
};

}  // namespace imagecpp
