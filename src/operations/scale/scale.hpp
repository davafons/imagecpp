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

  int scaleX() const;
  int scaleY() const;
  Interpolation interpolation() const;

public slots:
  void setScaleX(int percentage);
  void setScaleY(int percentage);
  void setInterpolation(Interpolation interpolation);

protected:
  virtual void imageOperationImpl(Image* new_image) override;
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  QRgb nearestNeighbour(float x, float y, const Image* old_image) const;
  QRgb bilineal(float x, float y, const Image* old_image) const;

private:
  int x_percentage{100};
  int y_percentage{100};

  Interpolation interpolation_type_{Interpolation::NN};
};

};  // namespace imagecpp
