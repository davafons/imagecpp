#include "imagedifference.hpp"

namespace imagecpp {

ImageDifference::ImageDifference(Document* document)
    : PointOperation(document, tr("Image difference")) {}

const Image* ImageDifference::secondImage() const {
  return second_image_;
}

void ImageDifference::setSecondImage(const Image* image) {
  second_image_ = image;

  emit propertyChanged();
}

QRgb ImageDifference::pointOperationImpl(int x, int y, QRgb color) {

  QRgb second_image_color = second_image_->pixel(x, y);

  int red_diff = std::abs(qRed(color) - qRed(second_image_color));
  int green_diff = std::abs(qGreen(color) - qGreen(second_image_color));
  int blue_diff = std::abs(qBlue(color) - qBlue(second_image_color));

  return qRgb(red_diff, green_diff, blue_diff);
}

void ImageDifference::imageOperationImpl(Image* new_image) {
  if (second_image_ == nullptr) {
    return;
  }

  // Images must have same size
  if (new_image->size() != second_image_->size()) {
    return;
  }

  PointOperation::imageOperationImpl(new_image);
}

}  // namespace imagecpp
