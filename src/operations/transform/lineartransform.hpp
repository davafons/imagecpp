#pragma once

#include <QChart>
#include <QIntValidator>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QSpinBox>
#include <map>

#include "operations/private/lutoperation.hpp"

namespace imagecpp {

class LinearTransform : public LutOperation {
  Q_OBJECT

public:
  using StepsList = std::map<int, int>;

public:
  explicit LinearTransform(Document *document);

  const StepsList &steps() const;
  void setSteps(StepsList steps);

  void addStep(int in, int out);
  void removeStep(int in);

protected slots:
  virtual void fillLutTablesImpl() override;

private:
  StepsList steps_{{0, 0}, {255, 255}};
};

}  // namespace imagecpp
