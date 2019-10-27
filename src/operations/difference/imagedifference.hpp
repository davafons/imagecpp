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
  int threshold() const;

public slots:
  ImageDifference& setSecondImage(const Image* image);
  ImageDifference& setThreshold(int threshold);

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const override;
  virtual void imageOperationImpl(Image *new_image) override;

private:
  const Image* second_image_{nullptr};

  int threshold_{0};
};

}  // namespace imagecpp
