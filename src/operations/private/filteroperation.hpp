#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class FilterOperation : public PointOperation {
public:
  explicit FilterOperation(Document* document, const QString& name = "");
  virtual ~FilterOperation() = default;

protected:
  virtual void imageOperationImpl(Image* new_image) override;
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

  virtual void fillKernel() = 0;

protected:
  std::vector<std::vector<int>> kernel_;
};

}  // namespace imagecpp
