#include "histogram.hpp"

#include <QBarSet>
#include <QColor>
#include <QDebug>
#include <QElapsedTimer>
#include <cmath>

namespace imagecpp {

/*!
 *  \class Histogram
 *  \brief Class representing a Histogram for a RGB image.
 */

/*!
 *  Construcs a Histogram object from an image, if passed.
 */
Histogram::Histogram(const Image *image, QObject *parent) : QObject(parent) {
  if (image) {
    generateHistogram(image);
  }
}

/*!
 *  Copy-constructs the histogram.
 */
Histogram::Histogram(const Histogram &other) {
  red_ = other.red_;
  green_ = other.green_;
  blue_ = other.blue_;
}

/*!
 *  Move-construcs the histogram.
 */
Histogram::Histogram(Histogram &&other) : Histogram() {
  swap(*this, other);
}

/*!
 *  Copy assignment of the histogram.
 */
Histogram &Histogram::operator=(Histogram other) {
  swap(*this, other);

  return *this;
}

/*!
 *  Returns the mean as an average between the means of the RGB channels.
 */
float Histogram::mean() const {
  return (red().mean() + green().mean() + blue().mean()) / 3;
}

/*!
 *  Alias of standardDeviation()
 *
 *  \sa standardDeviation()
 */
float Histogram::stdev() const {
  return standardDeviation();
}

/*!
 *  Returns the standard deviation as an average between the stdevs of the RGB channels.
 */
float Histogram::standardDeviation() const {
  return (red().stdev() + green().stdev() + blue().stdev()) / 3;
}

/*!
 *  Returns the total number of pixels on the image.
 */
int Histogram::pixelCount() const {
  return pixel_count_;
}

/*!
 *  Returns the Red component of the histogram.
 */
const HistogramChannel &Histogram::red() const {
  return red_;
}

/*!
 *  Returns the Green component of the histogram.
 */
const HistogramChannel &Histogram::green() const {
  return green_;
}

/*!
 *  Returns the Blue component of the histogram.
 */
const HistogramChannel &Histogram::blue() const {
  return blue_;
}

/*!
 *  Swap two histograms altogether.
 */
void swap(Histogram &first, Histogram &second) {
  using std::swap;

  swap(first.red_, second.red_);
  swap(first.green_, second.green_);
  swap(first.blue_, second.blue_);
}

/*!
 *  Generate a new histogram from an RGB image, filling the three RGB channels.
 *
 *  Each time the histogram changes, the signal histogramChanged will be triggered.
 */
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

  pixel_count_ = image->pixelCount();

  qDebug() << "The histogram took" << timer.elapsed() << "ms to generate";

  emit histogramChanged(this);
}

}  // namespace imagecpp
