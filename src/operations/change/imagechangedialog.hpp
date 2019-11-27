#pragma once

#include "imagechange.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class ImagesListWidget;

class ImageChangeDialog : public ImageOperationDialog<ImageChange> {
  Q_OBJECT
public:
  explicit ImageChangeDialog(Document *document, QWidget *parent = nullptr);

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;

private:
  ImagesListWidget *images_list_widget_{nullptr};

  QSpinBox *threshold_spin_{nullptr};
  QPushButton *color_picker_button_{nullptr};
};

}  // namespace imagecpp
