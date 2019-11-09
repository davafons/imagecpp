#include "histogramchannel.hpp"

#include <cmath>

namespace imagecpp {

/*!
 *  \class HistogramChannel
 *  \brief Class representing a set of 256 values
 */

/*!
 *  Construcs a HistogramChannel object from an array of values. Also sets the name
 *  and color of the bars.
 */
HistogramChannel::HistogramChannel(const HistArray &h,
                                   const QString &name,
                                   const QColor &color)
    : h_(h), name_(name), color_(color) {

  auto is_not_zero = [](auto x) { return x != 0; };
  min_intensity_ = std::find_if(h.cbegin(), h.cend(), is_not_zero) - h.cbegin();
  max_intensity_ = h.crend() - std::find_if(h.crbegin(), h.crend(), is_not_zero) - 1;

  mode_ = std::max_element(h.cbegin(), h.cend()) - h.cbegin();
  acc_h_ = calculateCummulative(h);
  pixel_count_ = acc_h_[255];
  mean_ = calculateMean(h, pixel_count_);
  std_deviation_ = calculateStdDeviation(h, pixel_count_, mean_);
  entropy_ = calculateEntropy(h, pixel_count_);
}

/*!
 *  Returns the histogram values as a set of bars for representing on a chart.
 */
QtCharts::QBarSet *HistogramChannel::bars() const {
  return createBarSet(h_, name_, color_);
}

/*!
 *  Returns the histogram accumulated values as a set of bars for representing on a
 *  chart.
 */
QtCharts::QBarSet *HistogramChannel::cummulativeBars() const {
  return createBarSet(acc_h_, name_, color_);
}

QtCharts::QBarSet *HistogramChannel::cummulativeBarsNormalized() const {
  return createBarSet(acc_h_, name_, color_, pixelCount());
}

/*!
 *  Returns the mean of the histogram.
 */
float HistogramChannel::mean() const {
  return mean_;
}

/*!
 *  Alias of standardDeviation
 *
 *  \sa standardDeviation()
 */
float HistogramChannel::stdev() const {
  return standardDeviation();
}

/*!
 *  Returns the standard deviation of the histogram.
 */
float HistogramChannel::standardDeviation() const {
  return std_deviation_;
}

/*!
 *  Returns the entropy of the histogram.
 */
float HistogramChannel::entropy() const {
  return entropy_;
}

/*!
 *  Returns the mode of the histogram.
 */
int HistogramChannel::mode() const {
  return mode_;
}

/*!
 *  Returns the value corresponding with the mode of the histogram.
 */
int HistogramChannel::modeValue() const {
  return h_[mode_];
}

/*!
 *  Returns the index on the histogram corresponding with the first value != 0.
 */
int HistogramChannel::minIntensity() const {
  return min_intensity_;
}

/*!
 *  Returns the index on the histogram corresponding with the last value != 0.
 */
int HistogramChannel::maxIntensity() const {
  return max_intensity_;
}

/*!
 *  Returns the number of pixels on the whole histogram.
 */
int HistogramChannel::pixelCount() const {
  return pixel_count_;
}

/*!
 *  Swaps to HistogramChannel altogether.
 */
void swap(HistogramChannel &first, HistogramChannel &second) {
  using std::swap;

  swap(first.h_, second.h_);
  swap(first.acc_h_, second.acc_h_);

  swap(first.mean_, second.mean_);
  swap(first.std_deviation_, second.std_deviation_);
  swap(first.entropy_, second.entropy_);

  swap(first.mode_, second.mode_);

  swap(first.pixel_count_, second.pixel_count_);
  swap(first.min_intensity_, second.min_intensity_);
  swap(first.max_intensity_, second.max_intensity_);

  swap(first.name_, second.name_);
  swap(first.color_, second.color_);
}

/*!
 *  Calculates and returns an accumulative histogram from a normal histogram.
 */
HistogramChannel::HistArray HistogramChannel::calculateCummulative(const HistArray &h) {
  HistArray acc_h;
  int accumulated = 0;

  for (size_t i = 0; i < h.size(); ++i) {
    accumulated += h[i];

    acc_h[i] = accumulated;
  }

  return acc_h;
}

/*!
 *  Calculates and returns the mean of the passed histogram h.
 */
float HistogramChannel::calculateMean(const HistArray &h, int pixel_count) {
  float mean = 0.0f;

  for (size_t i = 1; i < h.size(); ++i) {
    mean += i * h[i];
  }

  mean /= pixel_count;

  return mean;
}

/*!
 *  Calculates and returns the standard deviation of the passed histogram h.
 */
float HistogramChannel::calculateStdDeviation(const HistArray &h,
                                              int pixel_count,
                                              float mean) {
  float deviation = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    deviation += std::pow(i - mean, 2) * h[i];
  }

  deviation /= pixel_count;

  return std::sqrt(deviation);
}

/*!
 *  Calculates the entropy of the passed histogram h.
 */
float HistogramChannel::calculateEntropy(const HistArray &h, int pixel_count) {
  float entropy = 0.0f;

  for (size_t i = 0; i < h.size(); ++i) {
    if (h[i] <= 0) {  // log of zero is infinite
      continue;
    }

    float p_i = float(h[i]) / pixel_count;
    entropy += p_i * std::log2(p_i);
  }

  return -entropy;
}

/*!
 *  Returns a barset created from the histogram array. Name and color must be passed
 *  too.
 *
 *  The object invoking this function must take ownership of the QBarSet.
 */
QtCharts::QBarSet *HistogramChannel::createBarSet(const HistArray &h,
                                                  const QString &name,
                                                  const QColor &color,
                                                  int normalization_factor) {
  QtCharts::QBarSet *barset = new QtCharts::QBarSet(name);
  barset->setColor(color);
  barset->setBorderColor(color);

  for (const auto &i : h) {
    *barset << float(i) / normalization_factor;
  }

  return barset;
}

}  // namespace imagecpp
