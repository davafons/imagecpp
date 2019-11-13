#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Document;
class Image;

class ImageDifference : public PointOperation {
  Q_OBJECT

public:
  explicit ImageDifference(Document* document);
  virtual ~ImageDifference() = default;

  const Image* secondImage() const;

public slots:
  void setSecondImage(const Image* image);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  const Image* second_image_{nullptr};
};

}  // namespace imagecpp
