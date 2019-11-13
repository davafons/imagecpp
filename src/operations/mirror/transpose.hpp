#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Transpose : public PointOperation {
public:
  explicit Transpose(Document *document);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

  virtual void imageOperationImpl(Image *new_image) override;
};

}  // namespace imagecpp
