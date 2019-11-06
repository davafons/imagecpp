#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Specification : public PointOperation {
  Q_OBJECT

public:
  explicit Specification(Document *document);
  virtual ~Specification() = default;

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) const override;
};

}  // namespace imagecpp
