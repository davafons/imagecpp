#include "histogramview.hpp"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QDebug>
#include <QGraphicsLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMargins>
#include <QVBoxLayout>
#include <QValueAxis>

using namespace QtCharts;

namespace imagecpp {

HistogramView::HistogramView(QWidget *parent)
    : QWidget(parent), chart_(new QChart()), x_axis_(new QValueAxis()),
      y_axis_(new QValueAxis()), red_chart_radio_(new QRadioButton("Red")),
      green_chart_radio_(new QRadioButton("Green")),
      blue_chart_radio_(new QRadioButton("Blue")), bar_values_(new QLabel()) {

  setMouseTracking(true);

  // Setup chart properties
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
  chart_->setAcceptHoverEvents(true);

  // Setup widgets
  QVBoxLayout *vbox_layout = new QVBoxLayout();

  QGroupBox *rgb_box = new QGroupBox();
  QHBoxLayout *rgb_box_layout = new QHBoxLayout();

  red_chart_radio_->setChecked(true);

  rgb_box_layout->addWidget(red_chart_radio_);
  rgb_box_layout->addWidget(green_chart_radio_);
  rgb_box_layout->addWidget(blue_chart_radio_);

  rgb_box->setLayout(rgb_box_layout);

  QtCharts::QChartView *chart_view = new QtCharts::QChartView(chart_);
  chart_view->setRenderHint(QPainter::Antialiasing);

  vbox_layout->addWidget(chart_view);
  vbox_layout->addWidget(bar_values_);
  vbox_layout->addWidget(rgb_box);

  setLayout(vbox_layout);

  connect(red_chart_radio_, &QRadioButton::toggled, this,
          [this](bool checked) { setHistogram(active_histogram_); });
  connect(green_chart_radio_, &QRadioButton::toggled, this,
          [this](bool checked) { setHistogram(active_histogram_); });
  connect(blue_chart_radio_, &QRadioButton::toggled, this,
          [this](bool checked) { setHistogram(active_histogram_); });
}

void HistogramView::setHistogram(const Histogram *histogram) {
  if (histogram) {
    active_histogram_ = histogram;

    if (red_chart_radio_->isChecked()) {
      changeDisplayedBars(active_histogram_->redBars());
    } else if (green_chart_radio_->isChecked()) {
      changeDisplayedBars(active_histogram_->greenBars());
    } else if (blue_chart_radio_->isChecked()) {
      changeDisplayedBars(active_histogram_->blueBars());
    }
  }
}

void HistogramView::changeDisplayedBars(QtCharts::QBarSet *bars) {
  QBarSeries *series = new QBarSeries();
  series->append(bars);

  series->setBarWidth(1);

  chart_->removeAllSeries();
  chart_->addSeries(series);

  connect(series, &QAbstractBarSeries::hovered, this,
          [this](bool status, int index, QBarSet *barset) {
            if (status) {
              bar_values_->setText(QString("Index: %1\t-\tValue: %2")
                                       .arg(index)
                                       .arg(barset->at(index)));
            } else {
              bar_values_->clear();
            }
          });
}

} // namespace imagecpp
