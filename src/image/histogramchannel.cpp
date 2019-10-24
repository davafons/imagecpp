#include "histogramchannel.hpp"

#include <cmath>

namespace imagecpp {

HistogramChannel::HistogramChannel(const HistArray &h, const QString &name,
                                   const QColor &color)
    : h_(h), acc_h_(HistArray()), mean_(0.0f), std_deviation_(0.0f),
      entropy_(0.0f), mode_(0), pixel_count_(0), name_(name), color_(color) {
  // TODO: Check if empty is passed

  auto is_not_zero = [](auto x) { return x != 0; };
  min_intensity_ = std::find_if(h.cbegin(), h.cend(), is_not_zero) - h.cbegin();

  max_intensity_ =
      h.crend() - std::find_if(h.crbegin(), h.crend(), is_not_zero) - 1;
  // TODO: Minmax?

  mode_ = std::max_element(h.cbegin(), h.cend()) - h.cbegin();
  acc_h_ = calculateCummulative(h);
  pixel_count_ = acc_h_[255];
  mean_ = calculateMean(h, pixel_count_);
  std_deviation_ = calculateStdDeviation(h, pixel_count_, mean_);
  entropy_ = calculateEntropy(h, pixel_count_);
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
float HistogramChannel::entropy() const { return entropy_; }

int HistogramChannel::mode() const { return mode_; }
int HistogramChannel::modeValue() const { return h_[mode_]; }

int HistogramChannel::minIntensity() const { return min_intensity_; }
int HistogramChannel::maxIntensity() const { return max_intensity_; }
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

float HistogramChannel::calculateStdDeviation(const HistArray &h,
                                              int pixel_count, float mean) {
  float deviation = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    deviation += std::pow(i - mean, 2) * h[i];
  }

  deviation /= pixel_count;

  return std::sqrt(deviation);
}

float HistogramChannel::calculateEntropy(const HistArray &h, int pixel_count) {
  float entropy = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    if (h[i] <= 0) { // log of zero is infinite
      continue;
    }

    float p_i = float(h[i]) / pixel_count;
    entropy += p_i * std::log2(p_i);
  }

  return -entropy;
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
