#include "digitalization.hpp"

#include <cmath>

namespace imagecpp {

Digitalization::Digitalization(Document *document)
    : PointOperation(document, tr("Digitalization")) {}

int Digitalization::samplingSize() const {
  return sampling_size_;
}

int Digitalization::quantizationFactor() const {
  return quantization_factor_;
}

void Digitalization::setSamplingSize(int size) {
  sampling_size_ = size;

  sampling_table_up_to_date_ = false;

  emit propertyChanged();
}

void Digitalization::setQuantizationFactor(int factor) {
  quantization_factor_ = factor;

  quantization_values_up_to_date = false;

  emit propertyChanged();
}

QRgb Digitalization::pointOperationImpl(int x, int y, QRgb) {
  QRgb color = sampling_table_[y / sampling_size_][x / sampling_size_];

  int red_idx =
      std::round((float(qRed(color)) / 255) * (quantization_values_.size() - 1));
  int green_idx =
      std::round((float(qGreen(color)) / 255) * (quantization_values_.size() - 1));
  int blue_idx =
      std::round((float(qBlue(color)) / 255) * (quantization_values_.size() - 1));

  return qRgb(quantization_values_[red_idx],
              quantization_values_[green_idx],
              quantization_values_[blue_idx]);
}

void Digitalization::imageOperationImpl(Image *new_image) {
  if (!sampling_table_up_to_date_) {
    fillSamplingTable();
  }

  if (!quantization_values_up_to_date) {
    fillQuantizationValues();
  }

  PointOperation::imageOperationImpl(new_image);
}

void Digitalization::fillQuantizationValues() {
  int colors = std::pow(2, quantization_factor_);
  int step = 256 / colors;

  quantization_values_ = std::vector<int>(colors);

  quantization_values_[0] = 0;
  quantization_values_[quantization_values_.size() - 1] = 255;

  for (int i = 1; i < quantization_values_.size() - 1; ++i) {
    quantization_values_[i] = i * step;
  }

  quantization_values_up_to_date = true;
}

void Digitalization::fillSamplingTable() {
  int table_cols = std::ceil(float(oldImage()->height()) / sampling_size_);
  int table_rows = std::ceil(float(oldImage()->width()) / sampling_size_);

  sampling_table_ =
      std::vector<std::vector<QRgb>>(table_cols, std::vector<QRgb>(table_rows));

  for (int i = 0; i < sampling_table_.size(); ++i) {
    for (int j = 0; j < sampling_table_[i].size(); ++j) {
      long int red_av = 0;
      long int green_av = 0;
      long int blue_av = 0;

      int pixels = 0;

      for (int y = i * sampling_size_; y < (i + 1) * sampling_size_; ++y) {
        for (int x = j * sampling_size_; x < (j + 1) * sampling_size_; ++x) {

          if (x >= oldImage()->width() || y >= oldImage()->height()) {
            continue;
          }

          const QRgb color = oldImage()->pixel(x, y);

          red_av += qRed(color);
          green_av += qGreen(color);
          blue_av += qBlue(color);

          ++pixels;
        }
      }

      // Avoid division by zero
      pixels = std::max(pixels, 1);

      sampling_table_[i][j] =
          qRgb(red_av / pixels, green_av / pixels, blue_av / pixels);
    }
  }

  sampling_table_up_to_date_ = true;
}

}  // namespace imagecpp
