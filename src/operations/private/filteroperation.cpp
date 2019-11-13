#include "filteroperation.hpp"

namespace imagecpp {

FilterOperation::FilterOperation(Document* document, const QString& name)
    : PointOperation(document, name) {}

void FilterOperation::imageOperationImpl(Image* new_image) {
  fillKernel();

  PointOperation::imageOperationImpl(new_image);
}

QRgb FilterOperation::pointOperationImpl(int x, int y, QRgb) {
  int r_acc = 0;
  int g_acc = 0;
  int b_acc = 0;

  int pixels_count = 0;

  int kernel_half = kernel_.size() / 2;

  // qDebug() << x << y;

  for (int i = -kernel_half; i < kernel_half; ++i) {
    for (int j = -kernel_half; j < kernel_half; ++j) {
      int lx = x + i;
      int ly = y + j;

      if (lx < 0 || ly < 0 || lx >= oldImage()->width() || ly >= oldImage()->height()) {
        continue;
      }

      QRgb pixel = oldImage()->pixel(lx, ly);

      r_acc += qRed(pixel);
      g_acc += qGreen(pixel);
      b_acc += qBlue(pixel);

      ++pixels_count;
    }
  }

  pixels_count = std::max(pixels_count, 1);

  r_acc /= pixels_count;
  g_acc /= pixels_count;
  b_acc /= pixels_count;

  return qRgb(r_acc, g_acc, b_acc);
}

}  // namespace imagecpp
