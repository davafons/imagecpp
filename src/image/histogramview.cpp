#include "histogramview.hpp"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QDebug>
#include <QGraphicsLayout>
#include <QMargins>
#include <QValueAxis>

using namespace QtCharts;

namespace imagecpp {

HistogramView::HistogramView(QWidget *parent)
    : QChartView(nullptr, parent), chart_(new QChart()),
      x_axis_(new QValueAxis()), y_axis_(new QValueAxis()) {
  setRenderHint(QPainter::Antialiasing);

  QStringList categories;
  for (int i = 0; i < 256; ++i) {
    categories << QString(i);
  }

  x_axis_->setRange(0, 255);
  x_axis_->setLabelFormat("%d");
  x_axis_->setTickCount(9);

  y_axis_->setLabelFormat("%d");
  y_axis_->applyNiceNumbers();

  chart_->addAxis(x_axis_, Qt::AlignBottom);
  chart_->addAxis(y_axis_, Qt::AlignLeft);

  chart_->legend()->hide();
  chart_->setBackgroundRoundness(0);
  chart_->setMargins(QMargins(0, 0, 0, 0));

  setChart(chart_);
}

void HistogramView::setHistogram(const Histogram *histogram) {
  QBarSeries *series = new QBarSeries();
  series->append(histogram->redBars());

  series->setBarWidth(1);

  chart_->removeAllSeries();
  chart_->addSeries(series);
}

} // namespace imagecpp
