#include "histogram.hpp"

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>

namespace imagecpp {

Histogram::Histogram(QObject *parent) : QObject(parent) {
  h_r_ = new QtCharts::QBarSet("Red");
  h_g_ = new QtCharts::QBarSet("Green");
  h_b_ = new QtCharts::QBarSet("Blue");

  h_r_->setColor(Qt::red);
  h_r_->setBorderColor(Qt::red);
}

void Histogram::generateHistogram(const Image *image) {
  QElapsedTimer timer;
  timer.start();

  const int HISTOGRAM_SIZE = 256;

  std::array<int, HISTOGRAM_SIZE> r_acc;
  std::array<int, HISTOGRAM_SIZE> g_acc;
  std::array<int, HISTOGRAM_SIZE> b_acc;
  r_acc.fill(0);
  g_acc.fill(0);
  b_acc.fill(0);

  const QRgb *pixels = image->constBits();

  for (int p = 0; p < image->pixelCount(); ++p) {
    r_acc[qRed(pixels[p])] += 1;
    g_acc[qGreen(pixels[p])] += 1;
    b_acc[qBlue(pixels[p])] += 1;
  }

  for (int i = 0; i < HISTOGRAM_SIZE; ++i) {
    h_r_->append(r_acc[i]);
    h_g_->append(g_acc[i]);
    h_b_->append(b_acc[i]);
  }

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";
}

} // namespace imagecpp
