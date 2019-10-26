#include "histogram.hpp"

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>
#include <cmath>

namespace imagecpp {

Histogram::Histogram(const Image *image, QObject *parent) : QObject(parent) {
  if (image) {
    generateHistogram(image);
  }
}

Histogram::Histogram(const Histogram &other) {
  // r_h_ = other.r_h_;
  // g_h_ = other.g_h_;
  // b_h_ = other.b_h_;
}

float Histogram::mean() const {
  return (red().mean() + green().mean() + blue().mean()) / 3;
}

float Histogram::stdev() const {
  return standardDeviation();
}

float Histogram::standardDeviation() const {
  return (red().stdev() + green().stdev() + blue().stdev()) / 3;
}

const HistogramChannel &Histogram::red() const {
  return red_;
}
const HistogramChannel &Histogram::green() const {
  return green_;
}
const HistogramChannel &Histogram::blue() const {
  return blue_;
}

void Histogram::generateHistogram(const Image *image) {
  QElapsedTimer timer;
  timer.start();

  HistogramChannel::HistArray r_h;
  HistogramChannel::HistArray g_h;
  HistogramChannel::HistArray b_h;

  r_h.fill(0);
  g_h.fill(0);
  b_h.fill(0);

  const QRgb *pixels = image->constBits();

  for (int p = 0; p < image->pixelCount(); ++p) {
    r_h[qRed(pixels[p])] += 1;
    g_h[qGreen(pixels[p])] += 1;
    b_h[qBlue(pixels[p])] += 1;
  }

  red_ = HistogramChannel(r_h, "Red", Qt::red);
  green_ = HistogramChannel(g_h, "Green", Qt::green);
  blue_ = HistogramChannel(b_h, "Blue", Qt::blue);

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";

  emit histogramChanged(this);
}
}  // namespace imagecpp
