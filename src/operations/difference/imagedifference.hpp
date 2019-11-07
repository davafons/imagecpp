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
  int threshold() const;
  QColor diffColor() const;

public slots:
  void setSecondImage(const Image* image);
  void setThreshold(int threshold);
  void setDiffColor(const QColor& color);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) const override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  const Image* second_image_{nullptr};

  int threshold_{80};

  QColor diff_color_{Qt::red};
};

}  // namespace imagecpp
