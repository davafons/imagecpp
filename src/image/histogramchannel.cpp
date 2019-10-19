#include "histogramchannel.hpp"

namespace imagecpp {

HistogramChannel::HistogramChannel(const HistArray &h, const QString &name,
                                   const QColor &color)
    : h_(h), acc_h_(HistArray()), mean_(0.0f), std_deviation_(0.0f), mode_(0),
      pixel_count_(0), name_(name), color_(color) {

  if (!h.empty()) {
    mode_ = std::max_element(h.cbegin(), h.cend()) - h.cbegin();
    acc_h_ = calculateCummulative(h);
    pixel_count_ = acc_h_[255];
    mean_ = calculateMean(h, pixel_count_);
    std_deviation_ = calculateStdDeviation(h, pixel_count_, mean_);
  }
}

// Getters

QtCharts::QBarSet *HistogramChannel::bars() const {
  return createBarSet(h_, name_, color_);
}

QtCharts::QBarSet *HistogramChannel::cummulativeBars() const {
  return createBarSet(acc_h_, name_, color_);
}

float HistogramChannel::mean() const { return mean_; }

float HistogramChannel::standardDeviation() const { return std_deviation_; }

int HistogramChannel::mode() const { return mode_; }

int HistogramChannel::modeValue() const { return h_[mode_]; }

int HistogramChannel::pixelCount() const { return pixel_count_; }

// Private functions

HistogramChannel::HistArray
HistogramChannel::calculateCummulative(const HistArray &h) {
  HistArray acc_h;
  int accumulated = 0;

  for (size_t i = 0; i < h.size(); ++i) {
    accumulated += h[i];

    acc_h[i] = accumulated;
  }

  return acc_h;
}

float HistogramChannel::calculateMean(const HistArray &h, int pixel_count) {
  float mean = 0.0f;

  for (size_t i = 1; i < h.size(); ++i) {
    mean += i * h[i];
  }

  mean /= pixel_count;

  return mean;
}

// TODO: Check if correct
float HistogramChannel::calculateStdDeviation(const HistArray &h,
                                              int pixel_count, float mean) {
  float deviation = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    deviation += std::pow(h[i] - mean, 2);
  }

  deviation /= pixel_count;

  return std::sqrt(deviation);
}

QtCharts::QBarSet *HistogramChannel::createBarSet(const HistArray &h,
                                                  const QString &name,
                                                  const QColor &color) {
  QtCharts::QBarSet *barset = new QtCharts::QBarSet(name);
  barset->setColor(color);
  barset->setBorderColor(color);

  for (const auto &i : h) {
    *barset << i;
  }

  return barset;
}

} // namespace imagecpp
