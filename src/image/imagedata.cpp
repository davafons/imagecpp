#include <iostream>

#include "imagedata.hpp"

#include "image/proimage.hpp"

#include <QFileInfo>

int ImageData::next_id_ = 0;

ImageData::ImageData(ProImage *image, QObject *parent) : QObject(parent) {
  image_ = image;
}

// TODO: Delete undo stack

// TODO: Memory management
ImageData::ImageData(const ImageData &other) {
  QFileInfo other_file_path(other.filePath());
  file_path_ = QString(other_file_path.completeBaseName() + "_copy." +
                       other_file_path.completeSuffix());

  image_ = new ProImage(*other.image_);
  undo_stack_ = new QUndoStack();
}

void ImageData::setFilePath(QString file_path) {
  file_path_ = file_path;
  emit filePathChanged(file_path);
}

void ImageData::setImage(ProImage *image) {
  qInfo() << "Replacing image" << image_ << "with" << image;

  image_ = image;
  emit imageChanged(image);
}
