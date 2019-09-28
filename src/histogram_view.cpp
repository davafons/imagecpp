#include "histogram_view.hpp"

#include <QStringList>

HistogramView::HistogramView(const HistogramModel *hist_model)
    : hist_model_(hist_model) {
  QStackedBarSeries *series = new QStackedBarSeries();
  series->append(hist_model->hr_);
  series->append(hist_model->hg_);
  series->append(hist_model->hb_);
  series->append(hist_model_->hi_);

  addSeries(series);
  setTitle("Example stackedchart");

  QValueAxis *axisX = new QValueAxis();
  axisX->setRange(0, 255);
  axisX->setTickCount(16);
  addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  addAxis(axisY, Qt::AlignLeft);

  series->attachAxis(axisY);

  legend()->setVisible(true);
  legend()->setAlignment(Qt::AlignBottom);
}
