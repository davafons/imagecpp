#pragma once

#include <QtCharts>

#include "histogram_model.hpp"

// TODO: Must be a QChartView to add buttons and things
class HistogramView : public QChart {
public:
  HistogramView(const HistogramModel *hist_model);

private:
  const HistogramModel *hist_model_;
};
