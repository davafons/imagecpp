#include "imageoperation.hpp"

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

ImageOperation::ImageOperation(Document *data, const QString &name)
    : name_(name), data_(data), old_image_(data->copyImage()),
      target_image_(Image::empty(*data->image())) {

  connect(this, &ImageOperation::propertyChanged, this, [this] {
    up_to_date_ = false;

    if (live_update_) {
      generateTargetImage();
    }
  });

  connect(this, &ImageOperation::imageUpdated, this,
          [this] { up_to_date_ = true; });
}

const Image *ImageOperation::preview() {
  generateTargetImage();

  return target_image_;
}

QUndoCommand *ImageOperation::command() {
  generateTargetImage();

  return new ImageCommand(name_, data_, target_image_, old_image_);
}

void ImageOperation::toggleLiveUpdate(bool toggled) {
  live_update_ = toggled;

  if (live_update_) {
    generateTargetImage();
  }
}

void ImageOperation::generateTargetImage() {
  if (!up_to_date_) {
    qDebug() << "Generate target image";
    applyImageOperation();

    emit imageUpdated(target_image_);
  }
}

ImageOperation::ImageCommand::ImageCommand(const QString &name, Document *data,
                                           const Image *target_image,
                                           const Image *old_image)
    : QUndoCommand(name), data_(data), target_image_(target_image),
      old_image_(old_image) {}

void ImageOperation::ImageCommand::redo() {
  data_->setImage(target_image_->copy());
}

void ImageOperation::ImageCommand::undo() {
  data_->setImage(old_image_->copy());
}

} // namespace imagecpp
