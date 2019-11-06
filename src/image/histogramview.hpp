#pragma once

#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QComboBox>
#include <QHoverEvent>
#include <QLabel>
#include <QRadioButton>
#include <QValueAxis>

#include "histogram.hpp"

namespace imagecpp {

class HistogramView : public QWidget {
  Q_OBJECT

public:
  enum class Type { Default = 0, Cummulative = 1, CNormalized = 2 };

  explicit HistogramView(QWidget *parent = nullptr);
  virtual ~HistogramView() { delete chart_; }

public slots:
  void setHistogram(const Histogram *histogram);
  void setType(Type type);

private slots:
  void updateHistogramSeries();
  void setMarkerStyle(QLegendMarker *marker);

  void setLabelsText();
  void updateLabelTextFromMousePosition(int index);

protected:
  virtual QSize sizeHint() const override { return QSize(200, 200); }

  virtual bool eventFilter(QObject *object, QEvent *event) override;

private:
  // Chart attributes
  QtCharts::QChartView *chart_view_;
  QtCharts::QChart *chart_;

  QtCharts::QValueAxis *x_axis_;
  QtCharts::QValueAxis *y_axis_;

  // Histogram attributes
  Type type_;

  QtCharts::QBarSeries *red_series_;
  QtCharts::QBarSeries *green_series_;
  QtCharts::QBarSeries *blue_series_;

  // Widgets
  QLabel mouse_values_label_;

  QLabel count_label_;
  QLabel mean_label_;
  QLabel std_label_;
  QLabel entropy_label_;
  QLabel min_label_;
  QLabel max_label_;
  QLabel mode_label_;

  QComboBox *histogram_type_selector_;

  // Data
  const Histogram *active_histogram_;
};

}  // namespace imagecpp
