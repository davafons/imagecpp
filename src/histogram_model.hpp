#pragma once

#include <QBarSet>
#include <QImage>

#include <array>

class HistogramModel {
public:
  explicit HistogramModel(const QImage *image);

private:
  void buildHistogram();

public:
  const QImage *image_;

  QtCharts::QBarSet *hr_{new QtCharts::QBarSet("Red")};
  QtCharts::QBarSet *hg_{new QtCharts::QBarSet("Green")};
  QtCharts::QBarSet *hb_{new QtCharts::QBarSet("Blue")};
  QtCharts::QBarSet *hi_{new QtCharts::QBarSet("Intensity")};
};
