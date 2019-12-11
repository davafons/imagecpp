#include "rotation.hpp"

#include <QDebug>
#include <cmath>

namespace imagecpp {

Rotation::Rotation(Document *document) : PointOperation(document, tr("Rotation")) {}

int Rotation::angle() const {
  return angle_;
}

Rotation::Interpolation Rotation::interpolation() const {
  return interpolation_type_;
}

void Rotation::setAngle(int angle) {
  angle_ = (360 + (angle % 360)) % 360;

  emit propertyChanged();
}

void Rotation::setInterpolation(Interpolation interpolation) {
  interpolation_type_ = interpolation;

  emit propertyChanged();
}

QRgb Rotation::pointOperationImpl(int x, int y, QRgb) {
  switch (angle_) {
      // T.I
    case 90:
      return oldImage()->pixel(y, oldImage()->height() - x - 1);
      break;

    case 180:
      return oldImage()->pixel(oldImage()->width() - x - 1,
                               oldImage()->height() - y - 1);
      break;

    case 270:
      return oldImage()->pixel(oldImage()->width() - y - 1, x);
      break;

    default:
      break;
  }

  // T.I
  QPointF original = rotate(QPoint(x, y) + upper_left_, -angle_);

  if (!oldImage()->rect().contains(
          QPoint(std::round(original.x()), std::round(original.y())))) {
    return qRgba(0, 0, 0, 0);
  }

  switch (interpolation_type_) {
    case Interpolation::NN:
      return nearestNeighbour(original.x(), original.y(), oldImage());

    case Interpolation::Bilineal:
      return bilineal(original.x(), original.y(), oldImage());

    default:
      throw std::runtime_error("Undefined Interpolation type!");
  }
}  // namespace imagecpp

void Rotation::imageOperationImpl(Image *new_image) {
  QPointF A(0, 0);
  QPointF B(oldImage()->width(), 0);
  QPointF C(0, oldImage()->height());
  QPointF D(oldImage()->width(), oldImage()->height());

  A = rotate(A, angle_);
  B = rotate(B, angle_);
  C = rotate(C, angle_);
  D = rotate(D, angle_);

  float min_x = std::min(A.x(), std::min(B.x(), std::min(C.x(), D.x())));
  float max_x = std::max(A.x(), std::max(B.x(), std::max(C.x(), D.x())));
  float min_y = std::min(A.y(), std::min(B.y(), std::min(C.y(), D.y())));
  float max_y = std::max(A.y(), std::max(B.y(), std::max(C.y(), D.y())));

  upper_left_ = QPoint(min_x, min_y);
  lower_right_ = QPoint(max_x, max_y);

  qDebug() << upper_left_ << " and " << lower_right_;

  new_image->reset(max_x - min_x, max_y - min_y);

  for (int y = 0; y < new_image->height(); ++y) {
    QRgb *new_line = (QRgb *)new_image->scanLine(y);

    for (int x = 0; x < new_image->width(); ++x) {
      new_line[x] = pointOperationImpl(x, y, 0);
    }
  }
}

QPointF Rotation::rotate(QPointF point, float angle) {
  float x = point.x() * std::cos(radians(angle)) - point.y() * std::sin(radians(angle));
  float y = point.x() * std::sin(radians(angle)) + point.y() * std::cos(radians(angle));
  return QPoint(x, y);
}

float Rotation::radians(float angle) {
  return angle * (M_PI / 180);
}

QRgb Rotation::nearestNeighbour(float x, float y, const Image *old_image) const {
  int rounded_x = std::round(x);
  int rounded_y = std::round(y);

  return old_image->pixel(rounded_x, rounded_y);
}

QRgb Rotation::bilineal(float x, float y, const Image *old_image) const {
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
