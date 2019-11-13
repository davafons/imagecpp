#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Rotation : public PointOperation {
  Q_OBJECT

public:
  explicit Rotation(Document *document);
  virtual ~Rotation() = default;

  int degrees() const;

public slots:
  void setDegrees(int degrees);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb) override;
  virtual void imageOperationImpl(Image *new_image) override;

private:
  int degrees_{0};
};

}  // namespace imagecpp
