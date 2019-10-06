#include "imagemanager.hpp"

#include "image/proimage.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

// ProImage* ImageManager::iamge

void ImageManager::open() {
  qInfo() << "Selecting an image path to open";

  QString file_path =
      QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);

  qInfo() << "File selected: " << file_path;

  ImageData *image_data = new ImageData(new ProImage(file_path), this);
  Q_CHECK_PTR(image_data);
  image_data->setFilePath(file_path);

  qInfo() << "ImageData object created:" << image_data;

  emit imageOpened(image_data);
}

void ImageManager::save(ImageData *image_data) {
  saveAs(image_data, image_data->filePath());
}

void ImageManager::saveAs(ImageData *image_data, QString file_path) {
  if (!image_data) {
    return;
  }

  if (file_path.isEmpty()) {
    file_path =
        QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);
    image_data->setFilePath(file_path);
  }

  if (!image_data->image()->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Couldn't save image!"));
  } else {
    qDebug() << "Image saved";

    emit imageSaved(image_data, file_path);
  }
}

void ImageManager::duplicate(ImageData *other) {
  ImageData *duplicated_image = new ImageData(*other);

  emit imageOpened(duplicated_image);
}
