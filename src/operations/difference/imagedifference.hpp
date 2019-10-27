#pragma once

#include "operations/private/pixeloperation.hpp"

namespace imagecpp {

class Document;
class Image;

class ImageDifference : public PixelOperation {
  Q_OBJECT

public:
  explicit ImageDifference(Document* document);
  virtual ~ImageDifference() = default;

  const Image* secondImage() const;

public slots:
  ImageDifference& setSecondImage(const Image* image);

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const override;

private:
  const Image* second_image_{nullptr};
};

}  // namespace imagecpp
