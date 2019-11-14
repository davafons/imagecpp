#include "imagechangedialog.hpp"

#include "manager/documentsmanager.hpp"
#include "widgets/image/imageslistwidget.hpp"

namespace imagecpp {

ImageChangeDialog::ImageChangeDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<ImageChange>(document, parent) {

  images_list_widget_ = DocumentsManager::createImagesListWidget();

  threshold_spin_ = new QSpinBox();

  threshold_spin_->setRange(0, 255);
  threshold_spin_->setValue(operation().threshold());

  color_picker_button_ = new QPushButton(tr("Change color"));

  connect(threshold_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &ImageChange::setThreshold);

  connect(&operation(),
          &ImageChange::thresholdChanged,
          threshold_spin_,
          &QSpinBox::setValue);

  connect(color_picker_button_, &QPushButton::clicked, this, [this] {
    QColorDialog *dialog = new QColorDialog(this);

    connect(dialog,
            &QColorDialog::currentColorChanged,
            &operation(),
            &ImageChange::setDiffColor);

    dialog->show();
  });

  connect(images_list_widget_,
          &ImagesListWidget::imageChanged,
          &operation(),
          &ImageChange::setSecondImage);

  settings_layout_->addWidget(images_list_widget_);
  settings_layout_->addWidget(threshold_spin_);
  settings_layout_->addWidget(color_picker_button_);
}

void ImageChangeDialog::keyPressEvent(QKeyEvent *event) {
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

    case Qt::Key::Key_4:
      preview_display_->onImageUpdated(operation().differenceImage());
      break;
  }

  ImageOperationDialog::keyPressEvent(event);
}

}  // namespace imagecpp
