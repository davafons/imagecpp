#include "filteroperation.hpp"

namespace imagecpp {

FilterOperation::FilterOperation(Document* document, const QString& name)
    : PointOperation(document, name) {}

void FilterOperation::imageOperationImpl(Image* new_image) {
  fillKernel();

  for (const auto& row : kernel_) {
    for (const auto& col : row) {
      qDebug() << col;
    }
    qDebug() << "---";
  }

  PointOperation::imageOperationImpl(new_image);
}

QRgb FilterOperation::pointOperationImpl(int x, int y, QRgb color) {
  int r_acc = 0;
  int g_acc = 0;
  int b_acc = 0;

  int pixels_count = 0;

  // qDebug() << x << y;

  int kernel_h_rad = kernel_.size() / 2;

  for (int i = -kernel_h_rad; i < kernel_h_rad; ++i) {
    int kernel_v_rad = kernel_[i].size() / 2;

    for (int j = -kernel_v_rad; j < kernel_v_rad; ++j) {
      int lx = x + i;
      int ly = y + j;

      if (lx < 0 || ly < 0 || lx >= oldImage()->width() || ly >= oldImage()->height()) {
        continue;
      }

      QRgb pixel = oldImage()->pixel(lx, ly);

      int kx = i + kernel_h_rad;
      int ky = j + kernel_v_rad;

      r_acc += qRed(pixel) * kernel_[kx][ky];
      g_acc += qGreen(pixel) * kernel_[kx][ky];
      b_acc += qBlue(pixel) * kernel_[kx][ky];

      ++pixels_count;
    }
  }

  pixels_count = std::max(pixels_count, 1);

  r_acc /= pixels_count;
  g_acc /= pixels_count;
  b_acc /= pixels_count;

  return qRgba(r_acc, g_acc, b_acc, qAlpha(color));
}

}  // namespace imagecpp
