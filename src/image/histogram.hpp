#pragma once

#include <QBarSet>
#include <QColor>
#include <QObject>
#include <array>

#include "image/histogramchannel.hpp"
#include "image/image.hpp"

namespace imagecpp {

class Histogram : public QObject {
  Q_OBJECT

public:
  explicit Histogram(const Image *image = nullptr, QObject *parent = nullptr);
  virtual ~Histogram() = default;

  Histogram(const Histogram &other);
  Histogram(Histogram &&other);
  Histogram &operator=(Histogram other);

  float mean() const;
  float stdev() const;
  float standardDeviation() const;

  int pixelCount() const;

  const HistogramChannel &red() const;
  const HistogramChannel &green() const;
  const HistogramChannel &blue() const;

  friend void swap(Histogram &first, Histogram &second);

signals:
  void histogramChanged(const Histogram *histogram);

public slots:
  void generateHistogram(const Image *image);

private:
  HistogramChannel red_;
  HistogramChannel green_;
  HistogramChannel blue_;

  int pixel_count_;
};

}  // namespace imagecpp
