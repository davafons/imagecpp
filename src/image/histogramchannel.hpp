#pragma once

#include <QColor>
#include <QtCharts>

namespace imagecpp {

class HistogramChannel {

public:
  using HistArray = std::array<int, 256>;

public:
  explicit HistogramChannel(const HistArray &h = HistArray(),
                            const QString &name = "channel",
                            const QColor &color = Qt::black);

  QtCharts::QBarSet *bars() const;
  QtCharts::QBarSet *cummulativeBars() const;
  QtCharts::QBarSet *cummulativeBarsNormalized() const;

  float mean() const;
  float stdev() const;
  float standardDeviation() const;
  float entropy() const;

  int mode() const;
  int modeValue() const;

  int minIntensity() const;
  int maxIntensity() const;
  int pixelCount() const;

  friend void swap(HistogramChannel &first, HistogramChannel &second);

private:
  static HistArray calculateCummulative(const HistArray &h);
  static float calculateMean(const HistArray &h, int pixel_count);
  static float calculateStdDeviation(const HistArray &h, int pixel_count, float mean);
  static float calculateEntropy(const HistArray &h, int pixel_count);

  static QtCharts::QBarSet *createBarSet(const HistArray &h,
                                         const QString &name,
                                         const QColor &color,
                                         int pixel_count = 1);

private:
  HistArray h_;      // Histogram
  HistArray acc_h_;  // Accumulative

  float mean_{0.0f};
  float std_deviation_{0.0f};
  float entropy_{0.0f};

  int mode_{0};

  int pixel_count_{0};
  int min_intensity_{0};
  int max_intensity_{0};

  QString name_{"undefined"};
  QColor color_{Qt::black};
};

}  // namespace imagecpp
