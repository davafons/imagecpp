#include "imagemanager.hpp"

#include "image/proimage.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

// ProImage* ImageManager::iamge

void ImageManager::open() {
  QString file_path =
      QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);

  emit imageOpened(new ProImage(file_path, this));
}

void ImageManager::save(const ProImage *active_image) {
  saveAs(active_image, active_image->filePath());
}

void ImageManager::saveAs(const ProImage *active_image, QString file_path) {
  if (file_path.isEmpty()) {
    file_path =
        QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);
  }

  if (!active_image) {
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Select a window with an image!"));
    return;
  }

  if (!active_image->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Couldn't save image!"));
  } else {
    qDebug() << "Image saved";

    emit imageSaved(active_image);
  }
}

void ImageManager::duplicate(const ProImage *image) {
  ProImage *duplicated_image = new ProImage(*image);

  emit imageDuplicated(duplicated_image);
}
