#pragma once

#include <QColor>

#include "operations/private/imageoperation.hpp"

namespace imagecpp {

class Document;

class PixelOperation : public ImageOperation {
public:
  explicit PixelOperation(Document *document, const QString &name = "");
  virtual ~PixelOperation() = default;

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const = 0;
  virtual void imageOperationImpl(Image *new_image) override;
};
}  // namespace imagecpp
