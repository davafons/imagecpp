#include "lineartransform.hpp"

#include <QChartView>
#include <QLineEdit>
#include <QLineSeries>
#include <QPushButton>
#include <QSpinBox>
#include <QValueAxis>

namespace imagecpp {

/*!
 *  \class LinearTransform
 *  \brief Applies a linear transformation to an image.
 *
 *  The user can define the steps used on the transformation.
 */

/*!
 *  Construcs a LinearTransform operation object.
 */
LinearTransform::LinearTransform(Document *document)
    : LutOperation(document, "Linear transformation") {}

/*!
 *  Returns the list of steps used by the transformation.
 */
const LinearTransform::StepsList &LinearTransform::steps() const {
  return steps_;
}

/*!
 *  Sets a new list of steps.
 */
void LinearTransform::setSteps(std::map<int, int> steps) {
  steps_ = steps;

  emit propertyChanged();
}

/*!
 *  Adds a new step to the transformation.
 */
void LinearTransform::addStep(int in, int out) {
  steps_[in] = out;

  emit propertyChanged();
}

/*!
 *  Removes a step from the transformation. The deleted key must have the value "in". If
 *  the step isn't on the list, nothing will be deleted (but the propertyChanged signal
 *  will be triggered).
 */
void LinearTransform::removeStep(int in) {
  steps_.erase(in);

  emit propertyChanged();
}

/*!
 *  Implementation of the linear transform.
 *
 *  Iterate through all steps. Calculate the equation for the rect between the two steps
 *  and fill the lut table on the corresponding range.
 */
void LinearTransform::fillLutTablesImpl() {
  int x_i = steps_.begin()->first;
  int y_i = steps_.begin()->second;

  for (auto it = std::next(steps_.cbegin()); it != steps_.cend(); ++it) {
    int x_f = it->first;
    int y_f = it->second;

    int m = (y_f - y_i) / (x_f - x_i);
    int n = y_i - m * x_i;

    for (int vin = x_i; vin <= x_f; ++vin) {
      r_lut_[vin] = m * vin + n;
      g_lut_[vin] = m * vin + n;
      b_lut_[vin] = m * vin + n;
    }

    x_i = x_f;
    y_i = y_f;
  }
}

/*!
 *
 *
 *
 *
 *
 *
 */

// --- Dialog ---

Step::Step(int in, int out, QWidget *parent) : QWidget(parent) {

  // Layout representing a label - edit - label - edit row
  QHBoxLayout *hbox = new QHBoxLayout();

  in_edit_ = new QSpinBox();
  in_edit_->setRange(0, 255);
  in_edit_->setValue(in);

  out_edit_ = new QSpinBox();
  out_edit_->setRange(0, 255);
  out_edit_->setValue(out);

  remove_button_ = new QPushButton(tr("Remove"));

  // Adding to layout
  hbox->addWidget(new QLabel(tr("In")));
  hbox->addWidget(in_edit_);
  hbox->addWidget(new QLabel(tr("Out")));
  hbox->addWidget(out_edit_);
  hbox->addWidget(remove_button_);

  // Remove from layout when clicking on remove button
  connect(remove_button_, &QPushButton::clicked, this, [this] {
    setParent(nullptr);
    emit stepRemoved(this);
  });

  connect(in_edit_, qOverload<int>(&QSpinBox::valueChanged), this, [this] {
    emit inModified(this);
  });
  connect(out_edit_, qOverload<int>(&QSpinBox::valueChanged), this, [this] {
    emit outModified(this);
  });

  // Set final layout of the widget
  setLayout(hbox);
}

LinearTransformConfigDialog::LinearTransformConfigDialog(Document *document,
                                                         QWidget *parent)
    : OperationConfigDialog(document, parent),
      steps_layout_(new QVBoxLayout()),
      add_button_(new QPushButton(tr("Add new step"))),
      line_chart_(new QtCharts::QChart()) {

  QHBoxLayout *hbox = new QHBoxLayout();

  steps_layout_->setAlignment(Qt::AlignTop);
  steps_layout_->addWidget(add_button_, 0, Qt::AlignBottom);

  settings_layout_->addLayout(hbox);

  hbox->addLayout(steps_layout_);

  addNewStep(0, 0);
  addNewStep(255, 255);

  connect(add_button_,
          &QPushButton::clicked,
          this,
          &LinearTransformConfigDialog::addNextEmptyStep);

  // Setup  chart
  QtCharts::QValueAxis *x_axis = new QtCharts::QValueAxis();
  x_axis->setRange(0, 255);
  x_axis->setLabelFormat("%d");
  x_axis->setTickCount(5);

  QtCharts::QValueAxis *y_axis = new QtCharts::QValueAxis();
  y_axis->setRange(0, 255);
  y_axis->setLabelFormat("%d");
  y_axis->setTickCount(5);

  line_chart_->legend()->hide();
  line_chart_->addAxis(x_axis, Qt::AlignBottom);
  line_chart_->addAxis(y_axis, Qt::AlignLeft);

  QtCharts::QChartView *chart_view = new QtCharts::QChartView(line_chart_);
  chart_view->setRenderHint(QPainter::Antialiasing);
  chart_view->setRubberBand(QtCharts::QChartView::NoRubberBand);

  chart_view->setFixedSize(350, 350);
  hbox->addWidget(chart_view);
}

void LinearTransformConfigDialog::addNewStep(int in, int out) {
  Step *step = new Step(in, out);

  // Make connections between the step and the list
  connect(step, &Step::stepRemoved, this, &LinearTransformConfigDialog::removeStep);

  connect(step, &Step::inModified, this, &LinearTransformConfigDialog::inModified);

  connect(step, &Step::outModified, this, &LinearTransformConfigDialog::outModified);

  // Add to layout. Must be ordered
  insertStepOrderedInLayout(step);

  // Add to list of widgets
  steps_list_.append(step);

  qDebug() << "New step" << in << " " << out;

  updateSteps();
}

void LinearTransformConfigDialog::removeStep(Step *step) {
  // Remove from list and layout, permanently
  steps_list_.removeOne(step);
  steps_layout_->removeWidget(step);

  updateSteps();
}

void LinearTransformConfigDialog::inModified(Step *step) {
  steps_layout_->removeWidget(step);
  insertStepOrderedInLayout(step);

  updateSteps();
}

void LinearTransformConfigDialog::updateSteps() {
  std::map<int, int> steps_map;
  QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

  for (const auto &step : steps_list_) {
    steps_map[step->in()] = step->out();
  }

  // Now its sorted
  for (const auto &pair : steps_map) {
    series->append(pair.first, pair.second);
  }

  line_chart_->removeAllSeries();
  line_chart_->addSeries(series);

  operation_.setSteps(steps_map);

  // QLineSeries *series
}

void LinearTransformConfigDialog::outModified(Step *step) {
  updateSteps();
}

void LinearTransformConfigDialog::addNextEmptyStep() {
  if (steps_list_.size() == 256) {
    qDebug() << "Can't add more steps";
    // TODO: Popup?
  }

  for (int i = 0; i < 256; ++i) {
    bool found = false;
    for (const auto &pair : steps_list_) {
      if (i == pair->in()) {
        found = true;
      }
    }

    if (!found) {
      addNewStep(i, i);
      break;
    }
  }

  updateSteps();
}

void LinearTransformConfigDialog::insertStepOrderedInLayout(Step *step) {
  // Insert ordered on layout
  int index = -1;
  int closest_step = -1;
  for (const auto &s : steps_list_) {
    if (s->in() < step->in() && s->in() > closest_step) {
      closest_step = s->in();
      index = steps_layout_->indexOf(s);
    }
  }

  // Add to layout
  steps_layout_->insertWidget(index + 1, step);
}

}  // namespace imagecpp
