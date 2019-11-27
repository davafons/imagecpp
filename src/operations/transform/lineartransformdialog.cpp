#include "lineartransformdialog.hpp"

namespace imagecpp {

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

LinearTransformDialog::LinearTransformDialog(Document *document, QWidget *parent)
    : ImageOperationDialog(document, parent),
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
          &LinearTransformDialog::addNextEmptyStep);

  line_chart_->legend()->hide();

  QtCharts::QChartView *chart_view = new QtCharts::QChartView(line_chart_);
  chart_view->setRenderHint(QPainter::Antialiasing);
  chart_view->setRubberBand(QtCharts::QChartView::NoRubberBand);

  chart_view->setFixedSize(350, 350);
  hbox->addWidget(chart_view);
}

void LinearTransformDialog::addNewStep(int in, int out) {
  Step *step = new Step(in, out);

  // Make connections between the step and the list
  connect(step, &Step::stepRemoved, this, &LinearTransformDialog::removeStep);

  connect(step, &Step::inModified, this, &LinearTransformDialog::inModified);

  connect(step, &Step::outModified, this, &LinearTransformDialog::outModified);

  // Add to layout. Must be ordered
  insertStepOrderedInLayout(step);

  // Add to list of widgets
  steps_list_.append(step);

  qDebug() << "New step" << in << " " << out;

  updateSteps();
}

void LinearTransformDialog::removeStep(Step *step) {
  // Remove from list and layout, permanently
  steps_list_.removeOne(step);
  steps_layout_->removeWidget(step);

  updateSteps();
}

void LinearTransformDialog::inModified(Step *step) {
  steps_layout_->removeWidget(step);
  insertStepOrderedInLayout(step);

  updateSteps();
}

void LinearTransformDialog::updateSteps() {
  std::map<int, int> steps_map;

  QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

  for (const auto &step : steps_list_) {
    steps_map[step->in()] = step->out();
  }

  if (steps_map.count(0) == 0) {
    steps_map[0] = 0;
  }

  if (steps_map.count(255) == 0) {
    steps_map[255] = 255;
  }

  // Now its sorted
  for (const auto &pair : steps_map) {
    series->append(pair.first, pair.second);
    qDebug() << "x" << pair.first << "y" << pair.second;
  }

  line_chart_->removeAllSeries();
  line_chart_->addSeries(series);
  line_chart_->createDefaultAxes();

  line_chart_->axes()[0]->setRange(0, 255);
  line_chart_->axes()[1]->setRange(0, 255);

  operation().setSteps(steps_map);
}

void LinearTransformDialog::outModified(Step *step) {
  updateSteps();
}

void LinearTransformDialog::addNextEmptyStep() {
  if (steps_list_.size() == 255) {
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

void LinearTransformDialog::insertStepOrderedInLayout(Step *step) {
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
