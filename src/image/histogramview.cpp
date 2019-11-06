#include "histogramview.hpp"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QDebug>
#include <QFont>
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
    : QWidget(parent),
      chart_view_(new QChartView()),
      chart_(new QChart()),
      x_axis_(new QValueAxis()),
      y_axis_(new QValueAxis()),
      type_(Type::Default),
      red_series_(new QBarSeries()),
      green_series_(new QBarSeries()),
      blue_series_(new QBarSeries()),
      histogram_type_selector_(new QComboBox()),
      active_histogram_(nullptr) {

  QFont axis_font;
  axis_font.setPixelSize(10);

  // Create X axis
  x_axis_->setRange(0, 255);
  x_axis_->setLabelFormat("%d");
  x_axis_->setTickCount(5);
  x_axis_->setLabelsFont(axis_font);

  // Create Y axis
  y_axis_->setLabelFormat("%d");
  y_axis_->setMin(0);
  y_axis_->setLabelsFont(axis_font);

  // Attach each axis to chart
  chart_->addAxis(x_axis_, Qt::AlignBottom);
  chart_->addAxis(y_axis_, Qt::AlignLeft);

  // Set chart properties
  chart_->setBackgroundRoundness(0);
  chart_->setMargins(QMargins(0, 0, 0, 0));

  chart_->addSeries(red_series_);
  chart_->addSeries(green_series_);
  chart_->addSeries(blue_series_);

  // Setup series
  for (const auto &s : chart_->series()) {
    QBarSeries *bar_series = static_cast<QBarSeries *>(s);
    bar_series->setBarWidth(1.0f);
    bar_series->attachAxis(x_axis_);
    bar_series->attachAxis(y_axis_);
    bar_series->installEventFilter(this);
  }

  // Setup chart view
  chart_view_ = new QtCharts::QChartView(chart_);
  chart_view_->setRenderHint(QPainter::Antialiasing);

  // Important! Allow to register mouse over events handled on eventFilter
  chart_view_->setAttribute(Qt::WA_Hover);
  chart_view_->setRubberBand(QChartView::HorizontalRubberBand);
  chart_view_->installEventFilter(this);

  // Setup additional widgets
  QGroupBox *information_box = new QGroupBox();
  QVBoxLayout *information_layout = new QVBoxLayout();
  information_layout->addWidget(&count_label_);
  information_layout->addWidget(&mean_label_);
  information_layout->addWidget(&std_label_);
  information_layout->addWidget(&entropy_label_);
  information_layout->addWidget(&min_label_);
  information_layout->addWidget(&max_label_);
  information_layout->addWidget(&mode_label_);
  information_box->setLayout(information_layout);

  // Add histogram types to the selector
  histogram_type_selector_->addItem("Default");
  histogram_type_selector_->addItem("Cummulative");
  histogram_type_selector_->addItem("Cummul. Normalized");

  connect(histogram_type_selector_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          [this](int index) { setType(static_cast<Type>(index)); });

  // Tie all widgets together on a single vertical box
  QVBoxLayout *vbox_layout = new QVBoxLayout();
  vbox_layout->addWidget(chart_view_);
  vbox_layout->addWidget(histogram_type_selector_);
  vbox_layout->addWidget(&mouse_values_label_);
  vbox_layout->addWidget(information_box);

  setLayout(vbox_layout);
}

void HistogramView::setHistogram(const Histogram *histogram) {
  active_histogram_ = histogram;

  setLabelsText();

  updateHistogramSeries();
}

void HistogramView::setType(Type type) {
  type_ = type;

  updateHistogramSeries();
}

void HistogramView::updateHistogramSeries() {
  red_series_->clear();
  green_series_->clear();
  blue_series_->clear();

  if (!active_histogram_) {
    return;
  }

  int max_y_value = 0;

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

      // Highest Y-axis value is the total of pixels on the image
      max_y_value = active_histogram_->red().pixelCount();
      break;

    case Type::CNormalized:
      red_series_->append(active_histogram_->red().cummulativeBarsNormalized());
      green_series_->append(active_histogram_->green().cummulativeBarsNormalized());
      blue_series_->append(active_histogram_->blue().cummulativeBarsNormalized());

      max_y_value = 1.0f;
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

void HistogramView::setLabelsText() {
  if (!active_histogram_) {
    return;
  }

  // Placeholder string. Text is formmated to display %1 %2 %3 in Red/Green/Blue
  // colors
  QString rgb_placeholder_text =
      "<font color=\"red\">%1</font> <font color=\"green\">%2</font> "
      "<font color=\"blue\">%3</font>";

  // Some less verbose aliases for red/green/blue histogram channels
  auto red = active_histogram_->red();
  auto green = active_histogram_->green();
  auto blue = active_histogram_->blue();

  // Execute "method" for each rgb channel, and return the result as a formatted
  // string
  auto extract_rgb_values_as_text =
      [rgb_placeholder_text, &red, &green, &blue](auto method) -> QString {
    return rgb_placeholder_text.arg(std::bind(method, red)())
        .arg(std::bind(method, green)())
        .arg(std::bind(method, blue)());
  };

  // Update the labels with the formatted text for each attribute

  count_label_.setText(tr("Count: ") +
                       QString::number(active_histogram_->red().pixelCount()));

  mean_label_.setText(tr("Mean: ") +
                      extract_rgb_values_as_text(&HistogramChannel::mean));

  std_label_.setText(tr("Std: ") +
                     extract_rgb_values_as_text(&HistogramChannel::standardDeviation));

  entropy_label_.setText(tr("Entropy: ") +
                         extract_rgb_values_as_text(&HistogramChannel::entropy));

  min_label_.setText(tr("Min: ") +
                     extract_rgb_values_as_text(&HistogramChannel::minIntensity));

  max_label_.setText(tr("Max: ") +
                     extract_rgb_values_as_text(&HistogramChannel::maxIntensity));

  mode_label_.setText(tr("Mode: ") +
                      extract_rgb_values_as_text(&HistogramChannel::mode));
}

void HistogramView::setMarkerStyle(QLegendMarker *marker) {
  marker->setVisible(true);

  // Dim the marker, if series is not visible
  qreal alpha = 1.0;

  if (!marker->series()->isVisible()) alpha = 0.5;

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

bool HistogramView::eventFilter(QObject *object, QEvent *event) {
  if (object == chart_view_ && event->type() == QEvent::HoverMove) {
    QHoverEvent *hover_event = static_cast<QHoverEvent *>(event);

    // Get mouse coordinates
    QPoint cursor_pos = hover_event->pos();

    // Translate mouse coordinate to chart coordinates and save the position
    // in X
    int index = chart_->mapToValue(cursor_pos).x();

    // Clamp index to min and max values
    index = (index < x_axis_->min()) ? x_axis_->min() : index;
    index = (index > x_axis_->max()) ? x_axis_->max() : index;

    updateLabelTextFromMousePosition(index);

    return true;
  }

  return false;
}

void HistogramView::updateLabelTextFromMousePosition(int index) {
  if (!active_histogram_) {
    return;
  }

  QString rgb_placeholder_text =
      "<font color=\"red\">%1</font> <font color=\"green\">%2</font> "
      "<font color=\"blue\">%3</font>";

  QString index_text = tr("Index: ") + QString::number(index);

  int red_value = red_series_->barSets()[0]->at(index);
  int green_value = green_series_->barSets()[0]->at(index);
  int blue_vale = blue_series_->barSets()[0]->at(index);

  QString rgb_values_text =
      rgb_placeholder_text.arg(red_value).arg(green_value).arg(blue_vale);

  mouse_values_label_.setText(index_text + "\t\t" + rgb_values_text);
}
}  // namespace imagecpp
