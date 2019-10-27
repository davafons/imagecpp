#include "imagedifference.hpp"

namespace imagecpp {

ImageDifference::ImageDifference(Document* document)
    : PixelOperation(document, tr("Image difference")) {}

const Image* ImageDifference::secondImage() const {
  return second_image_;
}

ImageDifference& ImageDifference::setSecondImage(const Image* image) {
  second_image_ = image;

  emit propertyChanged();

  return *this;
}

QRgb ImageDifference::pixelOperationImpl(int x, int y, QRgb color) const {

  return color;
}

}  // namespace imagecpp
