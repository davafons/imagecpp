#include "imageoperation.hpp"

#include "image/document.hpp"
#include "image/proimage.hpp"

namespace imagecpp {

ImageOperation::ImageOperation(Document *data, const QString &name)
    : name_(name), data_(data), old_image_(data->copyImage()),
      modified_image_(ProImage::empty(*data->image())) {

  connect(this, &ImageOperation::propertyChanged, this, [this] {
    up_to_date_ = false;
    if (real_time_)
      generateImage();
  });

  connect(this, &ImageOperation::imageChanged, this,
          [this] { up_to_date_ = true; });
}

const ProImage *ImageOperation::preview() {
  if (!up_to_date_)
    generateImage();

  return modified_image_;
}

QUndoCommand *ImageOperation::command() {
  if (!up_to_date_) {
    generateImage();
  }
  return new ImageCommand(name_, data_, modified_image_, old_image_);
}

void ImageOperation::generateImage() {
  if (!up_to_date_) {
    for (int y = 0; y < modified_image_->height(); ++y) {
      for (int x = 0; x < modified_image_->width(); ++x) {
        modified_image_->setPixel(
            x, y, pixelOperation(x, y, old_image_->pixel(x, y)));
      }
    }

    emit imageChanged(modified_image_);
  }
}

ImageOperation::ImageCommand::ImageCommand(const QString &name, Document *data,
                                           const ProImage *modified_image,
                                           const ProImage *old_image)
    : QUndoCommand(name), data_(data), modified_image_(modified_image),
      old_image_(old_image) {}

void ImageOperation::ImageCommand::redo() {
  data_->setImage(modified_image_->copy());
}

void ImageOperation::ImageCommand::undo() {
  data_->setImage(old_image_->copy());
}

} // namespace imagecpp
