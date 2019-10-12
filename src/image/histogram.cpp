#include "histogram.hpp"

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>

namespace imagecpp {

Histogram::Histogram(QObject *parent) : QObject(parent) {
  r_h_.fill(0);
  g_h_.fill(0);
  b_h_.fill(0);
}

QtCharts::QBarSet *Histogram::redBars() const {
  return createBarSet(r_h_, Qt::red);
}

QtCharts::QBarSet *Histogram::greenBars() const {
  return createBarSet(g_h_, Qt::green);
}

QtCharts::QBarSet *Histogram::blueBars() const {
  return createBarSet(b_h_, Qt::blue);
}

void Histogram::generateHistogram(const Image *image) {
  QElapsedTimer timer;
  timer.start();

  r_h_.fill(0);
  g_h_.fill(0);
  b_h_.fill(0);

  const QRgb *pixels = image->constBits();

  for (int p = 0; p < image->pixelCount(); ++p) {
    r_h_[qRed(pixels[p])] += 1;
    g_h_[qGreen(pixels[p])] += 1;
    b_h_[qBlue(pixels[p])] += 1;
  }

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";

  emit histogramUpdated(this);
}

QtCharts::QBarSet *
Histogram::createBarSet(const std::array<int, HISTOGRAM_SIZE> &histogram,
                        const QColor &color) const {
  QtCharts::QBarSet *barset = new QtCharts::QBarSet(color.name());
  barset->setColor(color);
  barset->setBorderColor(color);

  qDebug() << "Starting to duplicate";
  qDebug() << histogram.size();
  for (const auto &part : histogram) {
    qDebug() << part;
    *barset << part;
  }

  return barset;
}
} // namespace imagecpp
