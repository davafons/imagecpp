#include "imageslistwidget.hpp"

#include <QDebug>
#include <QListWidgetItem>

#include "image/image.hpp"

namespace imagecpp {

ImagesListWidget::ImagesListWidget(QWidget *parent) : QListWidget(parent) {

  connect(this, &QListWidget::itemActivated, this, [this](QListWidgetItem *item) {
    ImageItem *image_item = dynamic_cast<ImageItem *>(item);
    if (image_item) {
      emit imageChanged(image_item->image());
    }

    qDebug() << "Item changed";
  });
}

void ImagesListWidget::addImage(const QString &name, const Image *image) {
  addItem(new ImageItem(name, image));
}

}  // namespace imagecpp
