#include "histogram_model.hpp"

#include <QDebug>
#include <QElapsedTimer>
#include <QRgb>

HistogramModel::HistogramModel(const QImage &image) : image_(image) {
  buildHistogram();
}

void HistogramModel::buildHistogram() {
  qDebug() << "Building histogram for image of size" << image_.size();
#ifdef QT_DEBUG
  QElapsedTimer timer;
  timer.start();
#endif

  for (int y = 0; y < image_.height(); ++y) {
    QRgb *line = (QRgb *)image_.constScanLine(y);
    for (int x = 0; x < image_.width(); ++x) {
      hr_[qRed(line[x])] += 1;
      hg_[qGreen(line[x])] += 1;
      hb_[qBlue(line[x])] += 1;
    }
  }

#ifdef QT_DEBUG
  qDebug() << "The histogram took" << timer.elapsed()
           << "milliseconds to build";
#endif
}
