#include "histogram.hpp"

#include <cmath>

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>

namespace imagecpp {

Channel::Channel(const HistArray &h, const QColor &color)
    : h_(h), acc_h_(HistArray()), mean_(0.0f), std_deviation_(0.0f),
      color_(color) {

  if (!h.empty()) {
    acc_h_ = calculateAccumulated(h);
    mean_ = calculateMean(h, acc_h_[255]);
    std_deviation_ = calculateStdDeviation(h, acc_h_[255], mean_);
  }
}

// Getters

QtCharts::QBarSet *Channel::bars() const { return createBarSet(h_, color_); }

QtCharts::QBarSet *Channel::accumulativeBars() const {
  return createBarSet(acc_h_, color_);
}

float Channel::mean() const { return mean_; }

float Channel::standardDeviation() const { return std_deviation_; }

// Private functions

Channel::HistArray Channel::calculateAccumulated(const HistArray &h) {
  HistArray acc_h;
  int accumulated = 0;

  for (size_t i = 0; i < h.size(); ++i) {
    accumulated += h[i];

    acc_h[i] = accumulated;
  }

  return acc_h;
}

float Channel::calculateMean(const HistArray &h, int pixel_count) {
  float mean = 0.0f;

  for (size_t i = 1; i < h.size(); ++i) {
    mean += i * h[i];
  }

  mean /= pixel_count;

  return mean;
}

// TODO: Check if correct
float Channel::calculateStdDeviation(const HistArray &h, int pixel_count,
                                     float mean) {
  float deviation = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    deviation += std::pow(h[i] - mean, 2);
  }

  deviation /= pixel_count;

  return std::sqrt(deviation);
}

QtCharts::QBarSet *Channel::createBarSet(const HistArray &h,
                                         const QColor &color) {
  QtCharts::QBarSet *barset = new QtCharts::QBarSet(color.name());
  barset->setColor(color);
  barset->setBorderColor(color);

  for (const auto &i : h) {
    *barset << i;
    qDebug() << color.name() << i;
  }

  return barset;
}

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

QtCharts::QBarSet *Histogram::redBars() const { return red_.bars(); }

QtCharts::QBarSet *Histogram::greenBars() const { return green_.bars(); }

QtCharts::QBarSet *Histogram::blueBars() const { return blue_.bars(); }

float Histogram::redMean() const { return red_.mean(); }

float Histogram::greenMean() const { return green_.mean(); }

float Histogram::blueMean() const { return blue_.mean(); }

void Histogram::generateHistogram(const Image *image) {
  QElapsedTimer timer;
  timer.start();

  Channel::HistArray r_h;
  Channel::HistArray g_h;
  Channel::HistArray b_h;

  r_h.fill(0);
  g_h.fill(0);
  b_h.fill(0);

  const QRgb *pixels = image->constBits();

  for (int p = 0; p < image->pixelCount(); ++p) {
    r_h[qRed(pixels[p])] += 1;
    g_h[qGreen(pixels[p])] += 1;
    b_h[qBlue(pixels[p])] += 1;
  }

  red_ = Channel(r_h, Qt::red);
  green_ = Channel(g_h, Qt::green);
  blue_ = Channel(b_h, Qt::blue);

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";

  emit histogramChanged(this);
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
