#include "histogram.hpp"

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>

namespace imagecpp {

Histogram::Histogram(const Image *image, QObject *parent)
    : QObject(parent), r_mean_(0), g_mean_(0), b_mean_(0) {
  r_h_.fill(0);
  g_h_.fill(0);
  b_h_.fill(0);

  if (image) {
    generateHistogram(image);
  }
}

Histogram::Histogram(const Histogram &other) {
  r_h_ = other.r_h_;
  g_h_ = other.g_h_;
  b_h_ = other.b_h_;
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

float Histogram::redMean() const { return r_mean_; }

float Histogram::greenMean() const { return g_mean_; }

float Histogram::blueMean() const { return b_mean_; }

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

  r_mean_ = calculateMean(r_h_, image->pixelCount());
  g_mean_ = calculateMean(g_h_, image->pixelCount());
  b_mean_ = calculateMean(b_h_, image->pixelCount());

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";

  emit histogramChanged(this);
}

int Histogram::calculateMean(const std::array<int, HISTOGRAM_SIZE> &h,
                             int size) const {
  float mean = 0;
  for (int i = 0; i < HISTOGRAM_SIZE; ++i) {
    mean += (i + 1) * h[i];
  }

  mean /= size;

  qDebug() << "Mean" << mean;

  return mean;
}

QtCharts::QBarSet *
Histogram::createBarSet(const std::array<int, HISTOGRAM_SIZE> &histogram,
                        const QColor &color) const {
  QtCharts::QBarSet *barset = new QtCharts::QBarSet(color.name());
  barset->setColor(color);
  barset->setBorderColor(color);

  for (const auto &part : histogram) {
    *barset << part;
  }

  return barset;
}
} // namespace imagecpp
