#include "histogramview.hpp"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QDebug>
#include <QGraphicsLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLegendMarker>
#include <QMargins>
#include <QVBoxLayout>
#include <QValueAxis>

using namespace QtCharts;

namespace imagecpp {

HistogramView::HistogramView(QWidget *parent)
    : QWidget(parent), chart_view_(new QChartView()), chart_(new QChart()),
      x_axis_(new QValueAxis()), y_axis_(new QValueAxis()),
      type_(Type::Default), red_series_(new QBarSeries()),
      green_series_(new QBarSeries()), blue_series_(new QBarSeries()),
      bar_values_(new QLabel()), mean_values_(new QLabel()),
      histogram_type_selector_(new QComboBox()) {

  // Setup chart properties
  setMouseTracking(true);

  // Create X axis
  x_axis_->setRange(0, 255);
  x_axis_->setLabelFormat("%d");
  x_axis_->setTickCount(9);

  // Create Y axis
  y_axis_->setLabelFormat("%d");
  y_axis_->applyNiceNumbers();

  // Attach axis to chart
  chart_->addAxis(x_axis_, Qt::AlignBottom);
  chart_->addAxis(y_axis_, Qt::AlignLeft);

  // Set chart properties
  chart_->setBackgroundRoundness(0);
  chart_->setMargins(QMargins(0, 0, 0, 0));
  chart_->setAcceptHoverEvents(true);

  chart_->addSeries(red_series_);
  chart_->addSeries(green_series_);
  chart_->addSeries(blue_series_);

  // Setup series
  red_series_->setBarWidth(1);
  red_series_->attachAxis(x_axis_);
  red_series_->attachAxis(y_axis_);

  green_series_->setBarWidth(1);
  green_series_->attachAxis(x_axis_);
  green_series_->attachAxis(y_axis_);

  blue_series_->setBarWidth(1);
  blue_series_->attachAxis(x_axis_);
  blue_series_->attachAxis(y_axis_);

  // Setup additional widgets
  mean_values_->setText("Mean: ");

  histogram_type_selector_->addItem("Default");
  histogram_type_selector_->addItem("Cummulative");

  connect(histogram_type_selector_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          [this](int index) { setType(static_cast<Type>(index)); });

  chart_view_ = new QtCharts::QChartView(chart_);
  chart_view_->setRenderHint(QPainter::Antialiasing);

  // Tie all widgets together on a single vertical box
  QVBoxLayout *vbox_layout = new QVBoxLayout();
  vbox_layout->addWidget(chart_view_);
  vbox_layout->addWidget(histogram_type_selector_);
  vbox_layout->addWidget(bar_values_);
  vbox_layout->addWidget(mean_values_);

  setLayout(vbox_layout);
}

void HistogramView::setHistogram(const Histogram *histogram) {
  active_histogram_ = histogram;

  updateHistogramSeries();
}

void HistogramView::setType(Type type) {
  type_ = type;

  updateHistogramSeries();
}

void HistogramView::updateHistogramSeries() {
  if (!active_histogram_) {
    return;
  }

  int max_y_value = 0;

  red_series_->clear();
  green_series_->clear();
  blue_series_->clear();

  switch (type_) {
  case Type::Default:
    red_series_->append(active_histogram_->red().bars());
    green_series_->append(active_histogram_->green().bars());
    blue_series_->append(active_histogram_->blue().bars());

    // Highest Y-axis value is the highest series
    max_y_value = std::max(active_histogram_->red().modeValue(),
                           std::max(active_histogram_->green().modeValue(),
                                    active_histogram_->blue().modeValue()));
    break;

  case Type::Cummulative:
    red_series_->append(active_histogram_->red().cummulativeBars());
    green_series_->append(active_histogram_->green().cummulativeBars());
    blue_series_->append(active_histogram_->blue().cummulativeBars());

    max_y_value = active_histogram_->red().pixelCount();
    break;

  default:
    qDebug() << "Unrecognised histogram type";
    break;
  }

  // Set max y axis value
  y_axis_->setMax(max_y_value);

  // Allow clicks to legend to show/hide series
  const auto markers = chart_->legend()->markers();
  for (QLegendMarker *marker : markers) {
    setMarkerStyle(marker);

    connect(marker, &QLegendMarker::clicked, this, [this] {
      QLegendMarker *marker = qobject_cast<QLegendMarker *>(sender());
      // Toggle the visibility of the attached series
      marker->series()->setVisible(!marker->series()->isVisible());
      // Update style
      setMarkerStyle(marker);
    });
  }
}

void HistogramView::setMarkerStyle(QLegendMarker *marker) {
  marker->setVisible(true);

  // Dim the marker, if series is not visible
  qreal alpha = 1.0;

  if (!marker->series()->isVisible())
    alpha = 0.5;

  QColor color;
  QBrush brush = marker->labelBrush();
  color = brush.color();
  color.setAlphaF(alpha);
  brush.setColor(color);
  marker->setLabelBrush(brush);

  brush = marker->brush();
  color = brush.color();
  color.setAlphaF(alpha);
  brush.setColor(color);
  marker->setBrush(brush);

  QPen pen = marker->pen();
  color = pen.color();
  color.setAlphaF(alpha);
  pen.setColor(color);
  marker->setPen(pen);
}
} // namespace imagecpp
