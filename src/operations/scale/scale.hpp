#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Scale : public PointOperation {
  Q_OBJECT

public:
  enum class Interpolation { NN, Bilineal };

public:
  explicit Scale(Document* document);
  virtual ~Scale() = default;

  float scaleX() const;
  float scaleY() const;

  Interpolation interpolation() const;

public slots:
  void setScaleX(float percentage);
  void setScaleY(float percentage);

  void setWidth(int width);
  void setHeight(int height);

  void setInterpolation(Interpolation interpolation);

protected:
  virtual void imageOperationImpl(Image* new_image) override;
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  QRgb nearestNeighbour(float x, float y, const Image* old_image) const;
  QRgb bilineal(float x, float y, const Image* old_image) const;

private:
  float x_percentage_{100};
  float y_percentage_{100};

  Interpolation interpolation_type_{Interpolation::NN};
};

};  // namespace imagecpp
