#include "color.hpp"

#include "image/proimage.hpp"

ToGrayscaleCommand::ToGrayscaleCommand(ProImage *image)
    : QUndoCommand(QIODevice::tr("To grayscale")), image_(image),
      old_image_data_(image->getImageData().copy()) {}

void ToGrayscaleCommand::redo() { qDebug() << "Redo"; }
void ToGrayscaleCommand::undo() {
  qDebug() << "Undo";
  image_->setImageData(old_image_data_);
}
