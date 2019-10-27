#pragma once

#include "lineartransform.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class Step : public QWidget {
  Q_OBJECT

public:
  Step(int in, int out, QWidget *parent = nullptr);

  int in() const { return in_edit_->text().toInt(); }
  int out() const { return out_edit_->text().toInt(); }

signals:
  void inModified(Step *step);
  void outModified(Step *step);
  void stepRemoved(Step *step);

public slots:
  void setIn(int in) {
    in_edit_->setValue(in);
    emit inModified(this);
  }
  void setOut(int out) { out_edit_->setValue(out); }

private:
  QSpinBox *in_edit_;
  QSpinBox *out_edit_;
  QPushButton *remove_button_;
};

class LinearTransformDialog : public ImageOperationDialog<LinearTransform> {
  Q_OBJECT

public:
  explicit LinearTransformDialog(Document *document, QWidget *parent = nullptr);
  virtual ~LinearTransformDialog() = default;

private slots:
  void addNewStep(int in, int out);
  void removeStep(Step *inout);

  void inModified(Step *step);
  void outModified(Step *step);

  void updateSteps();

private:
  void addNextEmptyStep();
  void insertStepOrderedInLayout(Step *step);

private:
  QVBoxLayout *steps_layout_;
  QList<Step *> steps_list_;

  QPushButton *add_button_;

  QtCharts::QChart *line_chart_;
};

}  // namespace imagecpp
