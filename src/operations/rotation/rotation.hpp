#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Rotation : public PointOperation {
  Q_OBJECT

public:
  enum class Interpolation { NN, Bilineal };

public:
  explicit Rotation(Document* document);
  virtual ~Rotation() = default;

  int angle() const;
  Interpolation interpolation() const;

public slots:
  void setAngle(int angle);
  void setInterpolation(Interpolation interpolation);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb) override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  QPointF rotate(QPointF point, float angle);

  float radians(float angle);

  QRgb nearestNeighbour(float x, float y, const Image* old_image) const;
  QRgb bilineal(float x, float y, const Image* old_image) const;

private:
  int angle_{0};

  QPointF upper_left_;
  QPointF lower_right_;

  Interpolation interpolation_type_{Interpolation::NN};
};

}  // namespace imagecpp
