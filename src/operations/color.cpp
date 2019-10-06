#include "color.hpp"

#include <QColor>

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

ToGrayscaleCommand::ToGrayscaleCommand(ImageData *data)
    : QUndoCommand(QIODevice::tr("To grayscale")), data_(data),
      old_image_(new ProImage(*data->image())) {}

void ToGrayscaleCommand::redo() {
  if (!modified_image_) {
    // modified_image_ = new ProImage(old_image_->width(), old_image_->height(),
    //                                old_image_->format());

    modified_image_ = new ProImage(*old_image_);

    qDebug() << "Modified image info:" << modified_image_->size()
             << modified_image_->getPixmap();

    for (int y = 0; y < modified_image_->height(); ++y) {
      for (int x = 0; x < modified_image_->width(); ++x) {
        // NTSC Formula
        QColor color = modified_image_->pixelColor(x, y);

        int gray = color.red() * 0.299f + color.green() * 0.587f +
                   color.blue() * 0.144f;

        modified_image_->setPixelColor(x, y,
                                       QColor(gray, gray, gray, color.alpha()));
      }
    }
  }

  data_->setImage(modified_image_);
}
void ToGrayscaleCommand::undo() { data_->setImage(old_image_); }
