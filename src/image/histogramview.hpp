#pragma once

#include <QChart>
#include <QChartView>
#include <QRadioButton>
#include <QValueAxis>
#include <QLabel>

#include "histogram.hpp"

namespace imagecpp {

class HistogramView : public QWidget {
  Q_OBJECT

public:
  explicit HistogramView(QWidget *parent = nullptr);
  virtual ~HistogramView() { delete chart_; }

public slots:
  void setHistogram(const Histogram *histogram);

protected:
  virtual QSize sizeHint() const { return QSize(200, 200); }

private slots:
  void changeDisplayedBars(QtCharts::QBarSet *bars);

private:
  QtCharts::QChart *chart_;

  QtCharts::QValueAxis *x_axis_;
  QtCharts::QValueAxis *y_axis_;

  QRadioButton *red_chart_radio_;
  QRadioButton *green_chart_radio_;
  QRadioButton *blue_chart_radio_;

  QLabel *bar_values_;
  QLabel *mean_values_;

  const Histogram *active_histogram_;
};

} // namespace imagecpp
