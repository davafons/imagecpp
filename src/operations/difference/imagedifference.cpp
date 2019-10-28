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

QRgb ImageDifference::diffColor() const {
  return diff_color_;
}

void ImageDifference::setSecondImage(const Image* image) {
  second_image_ = image;

  emit propertyChanged();
}

void ImageDifference::setThreshold(int threshold) {
  threshold_ = threshold;

  qDebug() << threshold_;

  emit propertyChanged();
}

void ImageDifference::setDiffColor(QRgb color) {
  diff_color_ = color;

  emit propertyChanged();
}

QRgb ImageDifference::pixelOperationImpl(int x, int y, QRgb color) const {

  QRgb second_image_color = second_image_->pixel(x, y);

  int red_diff = std::abs(qRed(color) - qRed(second_image_color));
  int green_diff = std::abs(qGreen(color) - qGreen(second_image_color));
  int blue_diff = std::abs(qBlue(color) - qBlue(second_image_color));

  if (red_diff > threshold_ && green_diff > threshold_ && blue_diff > threshold_) {
    return qRgba(255, 0, 0, 0);
  }

  return color;
}

void ImageDifference::imageOperationImpl(Image* new_image) {
  if (second_image_ == nullptr) {
    return;
  }

  // Images must have same size
  if (new_image->size() != second_image_->size()) {
    return;
  }

  PixelOperation::imageOperationImpl(new_image);
}

}  // namespace imagecpp
