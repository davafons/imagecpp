#include "filteroperation.hpp"

namespace imagecpp {

FilterOperation::FilterOperation(Document* document, const QString& name)
    : PointOperation(document, name) {}

void FilterOperation::imageOperationImpl(Image* new_image) {
  fillKernel();

  PointOperation::imageOperationImpl(new_image);
}

QRgb FilterOperation::pointOperationImpl(int x, int y, QRgb color) {
  int r_acc = 0;
  int g_acc = 0;
  int b_acc = 0;

  int value = 0;

  int kernel_v_rad = kernel_.size() / 2;

  for (int i = -kernel_v_rad; i <= kernel_v_rad; ++i) {
    int ly = y + i;

    if (ly < 0 || ly >= oldImage()->height()) {
      continue;
    }

    int kernel_h_rad = kernel_[i + kernel_v_rad].size() / 2;
    for (int j = -kernel_h_rad; j <= kernel_h_rad; ++j) {
      int lx = x + j;

      if (lx < 0 || lx >= oldImage()->width()) {
        continue;
      }

      QRgb pixel = oldImage()->pixel(lx, ly);

      int kx = j + kernel_h_rad;
      int ky = i + kernel_v_rad;

      r_acc += qRed(pixel) * kernel_[ky][kx];
      g_acc += qGreen(pixel) * kernel_[ky][kx];
      b_acc += qBlue(pixel) * kernel_[ky][kx];

      value += kernel_[ky][kx];
    }
  }

  value = std::max(value, 1);

  r_acc /= value;
  g_acc /= value;
  b_acc /= value;

  r_acc = std::min(std::max(r_acc, 0), 255);
  g_acc = std::min(std::max(g_acc, 0), 255);
  b_acc = std::min(std::max(b_acc, 0), 255);

  return qRgba(r_acc, g_acc, b_acc, qAlpha(color));
}

}  // namespace imagecpp
