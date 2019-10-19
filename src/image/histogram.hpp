#pragma once

#include <QBarSet>
#include <QColor>
#include <QObject>

#include <array>

#include "image/image.hpp"

namespace imagecpp {

class Channel {
public:
  using HistArray = std::array<int, 256>;

  explicit Channel(const HistArray &h = HistArray(),
                   const QColor &color = Qt::black);

  // Getters
  QtCharts::QBarSet *bars() const;
  QtCharts::QBarSet *accumulativeBars() const;

  float mean() const;
  float standardDeviation() const;

private:
  static HistArray calculateAccumulated(const HistArray &h);

  static float calculateMean(const HistArray &h, int pixel_count);

  static float calculateStdDeviation(const HistArray &h, int pixel_count,
                                     float mean);
  static QtCharts::QBarSet *createBarSet(const HistArray &h,
                                         const QColor &color);

private:
  HistArray h_;     // Histogram
  HistArray acc_h_; // Accumulative

  float mean_;
  float std_deviation_;

  QColor color_;
};

class Histogram : public QObject {
  Q_OBJECT

public:
  explicit Histogram(const Image *image = nullptr, QObject *parent = nullptr);
  virtual ~Histogram() = default;

  Histogram(const Histogram &other);

  // TODO: Alternative to return const
  QtCharts::QBarSet *redBars() const;
  QtCharts::QBarSet *greenBars() const;
  QtCharts::QBarSet *blueBars() const;

  float redMean() const;
  float greenMean() const;
  float blueMean() const;

signals:
  void histogramChanged(const Histogram *histogram);

public slots:
  void generateHistogram(const Image *image);

private:
  static const size_t HISTOGRAM_SIZE = 256;

  QtCharts::QBarSet *createBarSet(const std::array<int, HISTOGRAM_SIZE> &h,
                                  const QColor &color) const;

private:
  Channel red_;
  Channel green_;
  Channel blue_;
};

} // namespace imagecpp
