#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Document;
class Image;

class Digitalization : public PointOperation {
  Q_OBJECT

public:
  explicit Digitalization(Document* document);
  virtual ~Digitalization() = default;

  int samplingSize() const;
  int quantizationFactor() const;

public slots:
  void setSamplingSize(int size);
  void setQuantizationFactor(int factor);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;
  virtual void imageOperationImpl(Image* new_image) override;

private:
  void fillQuantizationValues();
  void fillSamplingTable();

private:
  int sampling_size_{4};
  std::vector<std::vector<QRgb>> sampling_table_{};

  int quantization_factor_{8};
  std::vector<int> quantization_values_{};

  bool sampling_table_up_to_date_{false};
  bool quantization_values_up_to_date{false};
};

}  // namespace imagecpp
