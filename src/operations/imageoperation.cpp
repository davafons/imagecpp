#include "imageoperation.hpp"

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

ImageOperation::ImageOperation(ImageData *data, const QString &name)
    : QUndoCommand(name), data_(data), old_image_(data->copyImage()),
      modified_image_(ProImage::empty(*data->image())) {}

void ImageOperation::redo() {
  if (!operation_done_) {
    calculateImage();
    operation_done_ = true;
  }

  data_->setImage(modified_image_);
}

void ImageOperation::undo() { data_->setImage(old_image_); }

void ImageOperation::calculateImage() {
  for (int y = 0; y < modified_image_->height(); ++y) {
    for (int x = 0; x < modified_image_->width(); ++x) {
      modified_image_->setPixel(x, y,
                                pixelOperation(x, y, old_image_->pixel(x, y)));
    }
  }
}
