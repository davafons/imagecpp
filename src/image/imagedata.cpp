#include "imagedata.hpp"

#include "image/proimage.hpp"

int ImageData::next_id_ = 0;

ImageData::ImageData(ProImage *image, QObject *parent) : QObject(parent) {
  image_ = image;
}

// TODO: Memory management
ImageData::ImageData(const ImageData &other) { image_ = other.image_; }
