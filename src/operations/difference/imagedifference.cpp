#include "imagedifference.hpp"

namespace imagecpp {

ImageDifference::ImageDifference(Document* document)
    : PixelOperation(document, tr("Image difference")) {}

const Image* ImageDifference::secondImage() const {
  return second_image_;
}

int ImageDifference::threshold() const {
  return threshold_;
}

ImageDifference& ImageDifference::setSecondImage(const Image* image) {
  second_image_ = image;

  emit propertyChanged();

  return *this;
}

ImageDifference& ImageDifference::setThreshold(int threshold) {
  threshold_ = threshold;

  emit propertyChanged();

  return *this;
}

QRgb ImageDifference::pixelOperationImpl(int x, int y, QRgb color) const {

  QRgb second_image_color = second_image_->pixel(x, y);
  QRgb difference_color = color - second_image_color;

  if (difference_color > threshold_) {
    return Qt::red;
  }

  return color;
}

void ImageDifference::imageOperationImpl(Image* new_image) {
  if (second_image_ == nullptr) {
    return;
  }

  PixelOperation::imageOperationImpl(new_image);
}

}  // namespace imagecpp
