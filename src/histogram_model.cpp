#include "histogram_model.hpp"

#include <QDebug>
#include <QElapsedTimer>
#include <QRgb>

HistogramModel::HistogramModel(const QImage *image) : image_(image) {
  buildHistogram();
}

void HistogramModel::buildHistogram() {
  qDebug() << "Building histogram for image of size" << image_->size();
#ifdef QT_DEBUG
  QElapsedTimer timer;
  timer.start();
#endif
  for (int i = 0; i < 256; ++i) {
    *hr_ << 0;
    *hg_ << 0;
    *hb_ << 0;
    *hi_ << 0;
  }

  for (int y = 0; y < image_->height(); ++y) {
    QRgb *line = (QRgb *)image_->constScanLine(y);
    for (int x = 0; x < image_->width(); ++x) {
      hr_->replace(qRed(line[x]), hr_->at(qRed(line[x])) + 1);
      hg_->replace(qGreen(line[x]), hg_->at(qGreen(line[x])) + 1);
      hb_->replace(qBlue(line[x]), hb_->at(qBlue(line[x])) + 1);
      hi_->replace(qGray(line[x]), hg_->at(qGray(line[x])) + 1);
    }
  }

#ifdef QT_DEBUG
  qDebug() << "The histogram took" << timer.elapsed()
           << "milliseconds to build";
#endif
}
