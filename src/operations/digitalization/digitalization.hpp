#pragma once

#include "operations/private/pixeloperation.hpp"

namespace imagecpp {

class Document;
class Image;

class Digitalization : public PixelOperation {
  Q_OBJECT

public:
  explicit Digitalization(Document* document);
  virtual ~Digitalization() = default;

  int samplingSize() const;

public slots:
  Digitalization& setSamplingSize(int size);

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  void fillSamplingTable();

private:
  int sampling_size_{2};

  std::vector<std::vector<QRgb>> sampling_table_;

  bool sampling_table_up_to_date_{false};
};

}  // namespace imagecpp
