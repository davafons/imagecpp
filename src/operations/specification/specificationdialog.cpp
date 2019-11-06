#include "specificationdialog.hpp"

#include "manager/documentsmanager.hpp"
#include "widgets/image/imageslistwidget.hpp"

namespace imagecpp {

SpecificationDialog::SpecificationDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Specification>(document, parent) {

  images_list_widget_ = DocumentsManager::createImagesListWidget();
  image_display_area_ = new ImageDisplayArea();

  connect(images_list_widget_,
          &ImagesListWidget::imageChanged,
          &operation(),
          &Specification::setSecondImage);

  connect(images_list_widget_,
          &ImagesListWidget::imageChanged,
          image_display_area_,
          &ImageDisplayArea::onImageOpened);

  settings_layout_->addWidget(images_list_widget_);
  settings_layout_->addWidget(image_display_area_);
}

}  // namespace imagecpp
