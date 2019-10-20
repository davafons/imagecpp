#pragma once

#include <QColor>
#include <QtCharts>

namespace imagecpp {
class HistogramChannel {
public:
  using HistArray = std::array<int, 256>;

  explicit HistogramChannel(const HistArray &h = HistArray(),
                            const QString &name = "channel",
                            const QColor &color = Qt::black);

  // Getters
  QtCharts::QBarSet *bars() const;
  QtCharts::QBarSet *cummulativeBars() const;

  float mean() const;
  float standardDeviation() const;

  int mode() const;
  int modeValue() const;

  int minIntensity() const;
  int maxIntensity() const;
  int pixelCount() const;

private:
  static HistArray calculateCummulative(const HistArray &h);

  static float calculateMean(const HistArray &h, int pixel_count);

  static float calculateStdDeviation(const HistArray &h, int pixel_count,
                                     float mean);
  static QtCharts::QBarSet *
  createBarSet(const HistArray &h, const QString &name, const QColor &color);

private:
  HistArray h_;     // Histogram
  HistArray acc_h_; // Accumulative

  float mean_;
  float std_deviation_;
  int mode_;

  int pixel_count_;
  int min_intensity_;
  int max_intensity_;

  QString name_;
  QColor color_;
};

} // namespace imagecpp
