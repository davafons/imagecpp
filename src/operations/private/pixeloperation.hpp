#pragma once

#include "operations/private/imageoperation.hpp"

namespace imagecpp {

class Document;

class PixelOperation : public ImageOperation {
  // TODO: Implement policys? (Cpu Threads, Cuda...)
public:
  PixelOperation(Document *data, const QString &name = "");
  virtual ~PixelOperation() = default;

protected slots:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const = 0;

private:
  virtual void applyImageOperation() override;
};
} // namespace imagecpp
