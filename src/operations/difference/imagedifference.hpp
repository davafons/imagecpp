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
  QRgb diffColor() const;

public slots:
  void setSecondImage(const Image* image);
  void setThreshold(int threshold);
  void setDiffColor(QRgb color);

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  const Image* second_image_{nullptr};

  int threshold_{80};

  QRgb diff_color_{Qt::red};
};

}  // namespace imagecpp
