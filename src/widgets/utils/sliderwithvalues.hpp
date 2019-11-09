#pragma once

#include <QLabel>
#include <QSlider>

class SliderWithValues : public QWidget {
  Q_OBJECT

public:
  SliderWithValues(Qt::Orientation orientation, QWidget *parent = nullptr);

  int minimum() const;
  int maximum() const;

signals:
  void valueChanged(double value);

public slots:
  void setMin(int min);
  void setMax(int max);
  void setRange(int min, int max);
  void setValue(double value);
  void setSubsteps(int substeps);

private:
  QSlider *slider_{nullptr};
  QLabel *value_label_{nullptr};

  int substeps_ = 10;
};
