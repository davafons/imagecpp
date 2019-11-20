#pragma once

#include "operations/difference/imagedifference.hpp"
#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Document;
class Image;

class ImageChange : public PointOperation {
  Q_OBJECT

public:
  explicit ImageChange(Document* document);
  virtual ~ImageChange() = default;

  int threshold() const;
  QColor diffColor();

  const Image* secondImage() const;
  const Image* differenceImage();

  const Histogram* diffImageHistogram() const;

signals:
  void thresholdChanged(int threshold);
  void diffHistogramGenerated(const Histogram* histogram);

public slots:
  void setThreshold(int threshold);
  void setDiffColor(const QColor& color);

  void setSecondImage(const Image* image);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  ImageDifference image_difference_operation_;

  Histogram* difference_image_histogram_;

  int threshold_{0};

  QColor diff_color_{Qt::red};
};

}  // namespace imagecpp
