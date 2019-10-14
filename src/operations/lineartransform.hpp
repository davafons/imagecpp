#pragma once

#include <QIntValidator>
#include <QLineEdit>
#include <QList>
#include <QSpinBox>
#include <QChart>

#include <map>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

#include <QPushButton>

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class LinearTransform : public LutOperation {
  Q_OBJECT

public:
  // Constructors

  explicit LinearTransform(Document *document,
                           const std::map<int, int> &steps = std::map<int, int>{
                               {0, 0}, {255, 255}});

  // Getters and Setters
  void addStep(int in, int out);
  void removeStep(int in);

  const std::map<int, int> &steps() const { return steps_; }
  void setSteps(std::map<int, int> steps);

protected slots:
  virtual void fillLutTables() override;

private:
  std::map<int, int> steps_;
};

// --- Dialog ---
//

// template <class T> class QItemValidator : public QIntValidator {
// public:
//   QItemValidator(const T &data, int min, int max, QObject *parent = nullptr)
//       : QIntValidator(min, max, parent), data_(data) {}
//
//   virtual QValidator::State validate(QString &input, int &pos) const override
//   {
//     QValidator::State range_state = QIntValidator::validate(input, pos);
//
//     if (range_state == QValidator::State::Acceptable) {
//       if (data_.count(input.toInt())) {
//         return QValidator::State::Invalid;
//       }
//
//       return QValidator::State::Acceptable;
//     }
//
//     return range_state;
//   }
//
// private:
//   const T &data_;
// };

/*
 *
 */
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

/*
 *
 */
class LinearTransformConfigDialog
    : public OperationConfigDialog<LinearTransform> {
  Q_OBJECT

public:
  explicit LinearTransformConfigDialog(Document *document,
                                       QWidget *parent = nullptr);
  virtual ~LinearTransformConfigDialog() = default;

private slots:
  void addNewStep(int in, int out);
  void removeStep(Step *inout);

  void inModified(Step *step);
  void outModified(Step *step);

  void updateSteps();

private:
  void addNextEmptyStep();
  void insertStepOrderedInLayout(Step *step);

  // int findNextGap(Step *step);

private:
  QVBoxLayout *steps_layout_;
  QList<Step *> steps_list_;

  QPushButton *add_button_;

  QtCharts::QChart *line_chart_;
};

} // namespace imagecpp
