#pragma once

#include <QChart>
#include <QChartView>
#include <QValueAxis>

#include "histogram.hpp"

namespace imagecpp {

class HistogramView : public QtCharts::QChartView {
public:
  explicit HistogramView(QWidget *parent = nullptr);

public slots:
  void setHistogram(const Histogram *histogram);

protected:
  virtual QSize sizeHint() const { return QSize(200, 200); }

private:
  QtCharts::QChart *chart_;

  QtCharts::QValueAxis *x_axis_;
  QtCharts::QValueAxis *y_axis_;
};

} // namespace imagecpp
