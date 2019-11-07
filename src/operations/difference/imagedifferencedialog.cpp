#include "imagedifferencedialog.hpp"

#include <QColorDialog>

#include "manager/documentsmanager.hpp"
#include "widgets/image/imageslistwidget.hpp"

namespace imagecpp {

ImageDifferenceDialog::ImageDifferenceDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<ImageDifference>(document, parent) {

  images_list_widget_ = DocumentsManager::createImagesListWidget();
  // image_display_area_ = new ImageDisplayArea();
  threshold_spin_ = new QSpinBox();

  threshold_spin_->setRange(0, 255);
  threshold_spin_->setValue(operation().threshold());

  color_picker_button_ = new QPushButton(tr("Change color"));

  connect(images_list_widget_,
          &ImagesListWidget::imageChanged,
          &operation(),
          &ImageDifference::setSecondImage);

  connect(threshold_spin_,
          qOverload<int>(&QSpinBox::valueChanged),
          &operation(),
          &ImageDifference::setThreshold);

  connect(color_picker_button_, &QPushButton::clicked, this, [this] {
    QColorDialog *dialog = new QColorDialog(this);

    connect(dialog,
            &QColorDialog::currentColorChanged,
            &operation(),
            &ImageDifference::setDiffColor);

    dialog->show();
  });

  settings_layout_->addWidget(images_list_widget_);
  settings_layout_->addWidget(threshold_spin_);
  settings_layout_->addWidget(color_picker_button_);
}

}  // namespace imagecpp
