#include "imagemanager.hpp"

#include "image/proimage.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

// ProImage* ImageManager::iamge

void ImageManager::open() {
  QString file_path =
      QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);

  emit imageOpened(new ImageData(new ProImage(file_path), this));
}

void ImageManager::save(ImageData *active_image) {
  saveAs(active_image, active_image->image()->filePath());
}

void ImageManager::saveAs(ImageData *active_image, QString file_path) {
  if (file_path.isEmpty()) {
    file_path =
        QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);
  }

  if (!active_image) {
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Select a window with an image!"));
    return;
  }

  if (!active_image->image()->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Couldn't save image!"));
  } else {
    qDebug() << "Image saved";

    emit imageSaved(active_image);
  }
}

void ImageManager::duplicate(ImageData *other) {
  ImageData *duplicated_image = new ImageData(*other);

  emit imageDuplicated(duplicated_image);
}
