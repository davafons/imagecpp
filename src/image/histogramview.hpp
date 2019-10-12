#pragma once

#include <QChart>
#include <QChartView>

#include "histogram.hpp"

namespace imagecpp {

class HistogramView : public QtCharts::QChartView {
public:
  explicit HistogramView(QWidget *parent = nullptr);

public slots:
  void setHistogram(const Histogram &histogram);

private:
  QtCharts::QChart *chart_;
};

} // namespace imagecpp
