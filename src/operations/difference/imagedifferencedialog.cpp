#include "imagedifferencedialog.hpp"

#include <QColorDialog>

#include "manager/documentsmanager.hpp"
#include "widgets/image/imageslistwidget.hpp"

namespace imagecpp {

ImageDifferenceDialog::ImageDifferenceDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<ImageDifference>(document, parent) {

  images_list_widget_ = DocumentsManager::createImagesListWidget();

  connect(images_list_widget_,
          &ImagesListWidget::imageChanged,
          &operation(),
          &ImageDifference::setSecondImage);

  settings_layout_->addWidget(images_list_widget_);
}

void ImageDifferenceDialog::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key::Key_1:
      preview_display_->onImageUpdated(operation().newImage());
      break;

    case Qt::Key::Key_2:
      preview_display_->onImageUpdated(operation().oldImage());
      break;

    case Qt::Key::Key_3:
      if (operation().secondImage() != nullptr) {
        preview_display_->onImageUpdated(operation().secondImage());
      }
      break;
  }

  ImageOperationDialog::keyPressEvent(event);
}

}  // namespace imagecpp
