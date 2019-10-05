#include "imagedata.hpp"

#include "image/proimage.hpp"

#include <QFileInfo>

int ImageData::next_id_ = 0;

ImageData::ImageData(ProImage *image, QObject *parent) : QObject(parent) {
  image_ = image;
}

// TODO: Memory management
ImageData::ImageData(const ImageData &other) {
  image_ = other.image_;
  QFileInfo other_file_path(other.filePath());
  file_path_ = QString(other_file_path.completeBaseName() + "_copy." +
                       other_file_path.completeSuffix());
}
