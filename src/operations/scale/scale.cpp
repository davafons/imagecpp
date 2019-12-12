#include "scale.hpp"

namespace imagecpp {

/*!
 *  \class Scale
 *  \brief Scale an image to the desired size.
 */

/*!
 *  Construct a Scale operation object.
 */

Scale::Scale(Document* document) : PointOperation(document) {
  // Update the operation name each time a property changes
  connect(this, &Scale::propertyChanged, this, [this] {
    setName(tr("Scale [%1%x%2% - %3]")
                .arg(x_percentage)
                .arg(y_percentage)
                .arg((interpolation_type_ == Interpolation::NN ? "NearestNeighbour"
                                                               : "Bilineal")));
  });
}

int Scale::scaleX() const {
  return x_percentage;
}

int Scale::scaleY() const {
  return y_percentage;
}

Scale::Interpolation Scale::interpolation() const {
  return interpolation_type_;
}

void Scale::setScaleX(int percentage) {
  x_percentage = percentage;

  emit propertyChanged();
}

void Scale::setScaleY(int percentage) {
  y_percentage = percentage;

  emit propertyChanged();
}

void Scale::setInterpolation(Interpolation interpolation) {
  interpolation_type_ = interpolation;

  emit propertyChanged();
}

void Scale::imageOperationImpl(Image* new_image) {
  // Set the new scale of the image (T.D)
  int new_width = (oldImage()->width() - 1) * x_percentage / 100;
  int new_height = (oldImage()->height() - 1) * y_percentage / 100;

  // Clamp values to 1x1
  new_width = std::max(1, new_width);
  new_height = std::max(1, new_height);

  new_image->reset(new_width, new_height);

  for (int y = 0; y < new_image->height(); ++y) {
    QRgb* new_line = (QRgb*)new_image->scanLine(y);

    for (int x = 0; x < new_image->width(); ++x) {
      new_line[x] = pointOperationImpl(x, y, 0);
    }
  }
}

QRgb Scale::pointOperationImpl(int x, int y, QRgb) {
  // T.I.
  float original_x = float(x / (float(x_percentage) / 100));
  float original_y = float(y / (float(y_percentage) / 100));

  switch (interpolation_type_) {
    case Interpolation::NN:
      return nearestNeighbour(original_x, original_y, oldImage());

    case Interpolation::Bilineal:
      return bilineal(original_x, original_y, oldImage());

    default:
      throw std::runtime_error("Undefined Interpolation type!");
  }
}

QRgb Scale::nearestNeighbour(float x, float y, const Image* old_image) const {
  int rounded_x = std::round(x);
  int rounded_y = std::round(y);

  return old_image->pixel(rounded_x, rounded_y);
}

QRgb Scale::bilineal(float x, float y, const Image* old_image) const {
  QRgb A = old_image->pixel(std::floor(x), std::ceil(y));
  QRgb B = old_image->pixel(std::ceil(x), std::ceil(y));
  QRgb C = old_image->pixel(std::floor(x), std::floor(y));
  QRgb D = old_image->pixel(std::ceil(x), std::floor(y));

  float p = x - std::floor(x);
  float q = y - std::floor(y);

  auto channel_op = [](int A, int B, int C, int D, float p, float q) {
    return C + (D - C) * p + (A - C) * q + (B + C - A - D) * p * q;
  };

  int red = channel_op(qRed(A), qRed(B), qRed(C), qRed(D), p, q);
  int green = channel_op(qGreen(A), qGreen(B), qGreen(C), qGreen(D), p, q);
  int blue = channel_op(qBlue(A), qBlue(B), qBlue(C), qBlue(D), p, q);
  int alpha = channel_op(qAlpha(A), qAlpha(B), qAlpha(C), qAlpha(D), p, q);

  return qRgba(red, green, blue, alpha);
}

}  // namespace imagecpp
