#include "histogramview.hpp"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QGraphicsLayout>
#include <QMargins>

using namespace QtCharts;

namespace imagecpp {

HistogramView::HistogramView(QWidget *parent)
    : QChartView(nullptr, parent), chart_(new QChart()) {
  setRenderHint(QPainter::Antialiasing);

  QStringList categories;
  for (int i = 0; i < 256; ++i) {
    categories << QString(i);
  }

  chart_->legend()->hide();
  chart_->setBackgroundRoundness(0);
  chart_->setMargins(QMargins(0, 0, 0, 0));

  setChart(chart_);
}

void HistogramView::setHistogram(const Histogram &histogram) {
  QBarSeries *series = new QBarSeries();
  series->append(histogram.red());

  series->setBarWidth(1);

  chart_->removeAllSeries();
  chart_->addSeries(series);
}

} // namespace imagecpp
