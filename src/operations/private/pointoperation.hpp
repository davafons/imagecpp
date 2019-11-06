#pragma once

#include <QColor>

#include "operations/private/imageoperation.hpp"

namespace imagecpp {

class Document;

class PointOperation : public ImageOperation {
public:
  explicit PointOperation(Document *document, const QString &name = "");
  virtual ~PointOperation() = default;

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) const = 0;
  virtual void imageOperationImpl(Image *new_image) override;
};
}  // namespace imagecpp
