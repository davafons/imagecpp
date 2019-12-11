#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Scale : public PointOperation {
  Q_OBJECT

public:
  explicit Scale(Document* document);
  virtual ~Scale() = default;

  int scaleX() const;
  int scaleY() const;

public slots:
  void setScaleX(int percentage);
  void setScaleY(int percentage);

protected:
  virtual void imageOperationImpl(Image* new_image) override;
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  int x_percentage{100};
  int y_percentage{100};
};

};  // namespace imagecpp
