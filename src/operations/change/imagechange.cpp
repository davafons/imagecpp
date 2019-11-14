#include "imagechange.hpp"

namespace imagecpp {

ImageChange::ImageChange(Document* document)
    : PointOperation(document, tr("Image change")),
      image_difference_operation_(document) {

  connect(this,
          &ImageOperation::newSelection,
          &image_difference_operation_,
          &ImageOperation::setSelection);

  emit propertyChanged();
}

int ImageChange::threshold() const {
  return threshold_;
}

QColor ImageChange::diffColor() {
  return diff_color_;
}

const Image* ImageChange::secondImage() const {
  return image_difference_operation_.secondImage();
}

const Image* ImageChange::differenceImage() {
  return image_difference_operation_.newImage();
}

void ImageChange::setThreshold(int threshold) {
  threshold_ = threshold;

  qDebug() << "New threshold" << threshold_;

  emit thresholdChanged(threshold);
  emit propertyChanged();
}

void ImageChange::setDiffColor(const QColor& color) {
  diff_color_ = color;

  emit propertyChanged();
}

void ImageChange::setSecondImage(const Image* image) {
  image_difference_operation_.setSecondImage(image);

  difference_image_histogram_.generateHistogram(image_difference_operation_.newImage());

  setThreshold(difference_image_histogram_.mean());

  qDebug() << "New second image";

  emit propertyChanged();
}

QRgb ImageChange::pointOperationImpl(int x, int y, QRgb color) {
  QRgb pixel = image_difference_operation_.newImage()->pixel(x, y);

  if (qRed(pixel) >= threshold_ && qGreen(pixel) >= threshold_ &&
      qBlue(pixel) >= threshold_) {
    return diff_color_.rgba();
  }

  return color;
}

}  // namespace imagecpp
