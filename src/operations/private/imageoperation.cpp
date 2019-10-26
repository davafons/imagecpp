#include "imageoperation.hpp"

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

/*!
 *  \class ImageOperation
 *  \brief Base class for all the image operations.
 *
 *  All the subclasses must implement imageOperationImpl, which as a result
 *  must update the new_image_ attribute.
 */

/*!
 *  Constructs the ImageOperation with a Document related and a operation name.
 */
ImageOperation::ImageOperation(Document* referenced_document, const QString& name)
    : new_image_(Image::empty(*referenced_document->image())),
      old_image_(referenced_document->copyImage()),
      referenced_document_(referenced_document),
      name_(name) {

  // After receiving the propertyChanged signal, generate new_image if the
  // "realtime update" option is toggled
  connect(this, &ImageOperation::propertyChanged, this, [this] {
    new_image_up_to_date_ = false;

    if (isRealtimeUpdateToggled()) {
      generateNewImage();
    }
  });

  // After toggling the "realtime update" option, generate new_image
  connect(this, &ImageOperation::realtimeUpdatetoggled, this, [this](bool toggled) {
    if (toggled) {
      generateNewImage();
    }
  });
}

/*!
 *  Returns the name of the operation.
 */
QString ImageOperation::name() const {
  return name_;
}

/*!
 *  Returns a QUndoCommand object representing the calculated operation.
 *   * The undo() method will set old_image_ as the referenced_document_ image.
 *   * The redo() method will set new_image_ as the referenced_document_ image.
 *
 *  This method should be used when an operation must be pushed to a QUndoStack.
 *
 *   TODO: Decide if set and save the histogram of the images too.
 */
QUndoCommand* ImageOperation::command() {
  generateNewImage();

  return new ImageCommand(name_, referenced_document_, new_image_, old_image_);
}

/*!
 *  Returns the result image after applying the operation. The image will be generated
 *  if it's not "up-to-date"
 *
 *  \sa isNewImageUpToDate()
 */
const Image* ImageOperation::newImage() {
  generateNewImage();

  return new_image_;
}

/*!
 *  Returns the old_image (the "source image" before applying the image operation)
 */
const Image* ImageOperation::oldImage() const {
  return old_image_;
}

/*!
 *  Returns the document that is being modified with the image operation.
 */
const Document* ImageOperation::referencedDocument() const {
  return referenced_document_;
}

/*!
 *  Returns the histogram of new_image
 */
const Histogram* ImageOperation::newHistogram() const {
  // TODO: To be implemented
  return nullptr;
}

/*!
 *  Returns the histogram of the old_image
 */
const Histogram* ImageOperation::oldHistogram() const {
  return referenced_document_->histogram();
}

/*!
 *  Returns the section of the image that will be used by the operation. If the
 *  selection is invalid, the whole image will be used.
 */
QRect ImageOperation::selection() const {
  return referenced_document_->selection();
}

/*!
 *  Returns if the image is being updated "on realtime" or not.
 *
 *  Updating an image "on realtime" means that every time the propertyChanged signal is
 *  triggered, the new_image_ will be regenerated and up-to-date.
 *
 *  This should only be toggled if the new_image if being previewed (i.e. on a window)
 *  while changing the properties of the operation.
 *
 *  \sa toggleRealtimeUpdate()
 */
bool ImageOperation::isRealtimeUpdateToggled() const {
  return realtime_update_toggled_;
}

/*!
 *  Returns if the image is "up-to-date".
 *
 *  An "up-to-date" image means that new_image has been recalculated after the newest
 *  propertyChanged signal.
 */
bool ImageOperation::isNewImageUpToDate() const {
  return new_image_up_to_date_;
}

/*!
 *  Toggles if the image will be updated "on realtime" or not.
 *
 *  Emits a signal with the boolean value assigned.
 *
 * \sa isRealtimeUpdateToggled()
 */
void ImageOperation::toggleRealtimeUpdate(bool toggled) {
  realtime_update_toggled_ = toggled;

  emit realtimeUpdatetoggled(toggled);
}

/*!
 *  Sets a new name for the operation.
 *
 *  Sometimes, the operation name changes depending on properties (i.e. Grayscale{PAL}
 *  vs Grayscale{NTSC}). Use this method to reflec that.
 */
void ImageOperation::setName(const QString& name) {
  name_ = name;
}

/*!
 *  TODO: Added for compatibility with Dialog.
 *  TODO: Explain better
 */
int ImageOperation::exec() const {
  return 1;
}

/*!
 *  Generates new_image if it isn't "up-to-date"
 *
 *  \sa isNewImageUpToDate()
 */
void ImageOperation::generateNewImage() {
  if (!isNewImageUpToDate()) {

    imageOperationImpl(new_image_);

    new_image_up_to_date_ = true;
  }
}

/*!
 *
 *
 *
 *
 *
 *
 *
 *
 */

ImageOperation::ImageCommand::ImageCommand(const QString& name,
                                           Document* document,
                                           const Image* target_image,
                                           const Image* old_image)
    : QUndoCommand(name),
      document_(document),
      target_image_(target_image),
      old_image_(old_image) {}

void ImageOperation::ImageCommand::redo() {
  document_->setImage(target_image_->copy());
}

void ImageOperation::ImageCommand::undo() {
  document_->setImage(old_image_->copy());
}

}  // namespace imagecpp
