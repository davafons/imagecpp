#include "sliderwithvalues.hpp"

#include <QHBoxLayout>

SliderWithValues::SliderWithValues(Qt::Orientation orientation, QWidget* parent)
    : QWidget(parent) {

  slider_ = new QSlider(orientation);
  slider_->setMinimumSize(140, 20);
  value_label_ = new QLabel();

  value_label_->setFixedSize(40, 10);

  connect(this, &SliderWithValues::valueChanged, this, [this](double value) {
    value_label_->setText(QString::number(value));
  });

  connect(slider_, &QSlider::valueChanged, this, [this](int value) {
    double actual_value = float(value) / substeps_;
    emit valueChanged(actual_value);
  });

  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->addWidget(slider_);
  layout->addWidget(value_label_);

  setLayout(layout);
}

int SliderWithValues::minimum() const {
  return slider_->minimum();
}
int SliderWithValues::maximum() const {
  return slider_->maximum();
}

void SliderWithValues::setMin(int min) {
  slider_->setMinimum(min);
}
void SliderWithValues::setMax(int max) {
  slider_->setMaximum(max);
}
void SliderWithValues::setRange(int min, int max) {
  slider_->setRange(min, max * substeps_);
}
void SliderWithValues::setValue(double value) {
  slider_->setValue(value * substeps_);
}
void SliderWithValues::setSubsteps(int substeps) {
  int max = maximum() / substeps_;

  substeps_ = substeps;

  setMax(max * substeps_);
}
