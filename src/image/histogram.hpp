#pragma once

#include <QBarSet>
#include <QObject>
#include <array>

#include "image/image.hpp"

namespace imagecpp {

class Histogram : public QObject {
  Q_OBJECT

public:
  explicit Histogram(const Image *image = nullptr, QObject *parent = nullptr);
  virtual ~Histogram() = default;

  Histogram(const Histogram& other);

  // TODO: Alternative to return const
  QtCharts::QBarSet *redBars() const;
  QtCharts::QBarSet *greenBars() const;
  QtCharts::QBarSet *blueBars() const;

signals:
  void histogramChanged(const Histogram *histogram);

public slots:
  void generateHistogram(const Image *image);

private:
  static const size_t HISTOGRAM_SIZE = 256;

  QtCharts::QBarSet *createBarSet(const std::array<int, HISTOGRAM_SIZE> &h,
                                  const QColor &color) const;

private:
  std::array<int, HISTOGRAM_SIZE> r_h_;
  std::array<int, HISTOGRAM_SIZE> g_h_;
  std::array<int, HISTOGRAM_SIZE> b_h_;
};

} // namespace imagecpp
