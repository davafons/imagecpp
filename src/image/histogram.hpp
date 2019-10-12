#pragma once

#include <QBarSet>
#include <QObject>
#include <array>

#include "image/image.hpp"

namespace imagecpp {

class Histogram : public QObject {
  Q_OBJECT

public:
  Histogram(QObject *parent = nullptr);
  virtual ~Histogram() = default;

  // TODO: Alternative to return const
  QtCharts::QBarSet *red() const { return h_r_; }
  QtCharts::QBarSet *green() const { return h_g_; }
  QtCharts::QBarSet *blue() const { return h_b_; }

public slots:
  void generateHistogram(const Image *image);

private:
  QtCharts::QBarSet *h_r_;
  QtCharts::QBarSet *h_g_;
  QtCharts::QBarSet *h_b_;
};

} // namespace imagecpp
