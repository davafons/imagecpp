#include "digitalization.hpp"

#include <cmath>

namespace imagecpp {

Digitalization::Digitalization(Document *document)
    : PixelOperation(document, tr("Digitalization")) {
  setSamplingSize(2);  // Must be called on constructor to initialize the sampling table
}

int Digitalization::samplingSize() const {
  return sampling_size_;
}

void Digitalization::setSamplingSize(int size) {
  sampling_size_ = size;

  sampling_table_.resize(oldImage()->height() / sampling_size_,
                         std::vector<QRgb>(oldImage()->width() / sampling_size_));

  sampling_table_up_to_date_ = false;

  emit propertyChanged();
}

QRgb Digitalization::pixelOperationImpl(int x, int y, QRgb) const {
  return sampling_table_[y / sampling_size_][x / sampling_size_];
}

void Digitalization::imageOperationImpl(Image *new_image) {
  if (!sampling_table_up_to_date_) {
    fillSamplingTable();
  }

  PixelOperation::imageOperationImpl(new_image);
}

void Digitalization::fillSamplingTable() {
  for (int i = 0; i < sampling_table_.size(); ++i) {
    for (int j = 0; j < sampling_table_[i].size(); ++j) {
      int red_av = 0;
      int green_av = 0;
      int blue_av = 0;

      int pixels = 1;

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

      sampling_table_[i][j] =
          qRgb(red_av / pixels, green_av / pixels, blue_av / pixels);
    }
  }

  sampling_table_up_to_date_ = true;

  qDebug() << "Sampling table calculated";
}

}  // namespace imagecpp
