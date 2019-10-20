#pragma once

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

#include <QDoubleSpinBox>

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class BrightnessAndConstrast : public LutOperation {
  Q_OBJECT

public:
  BrightnessAndConstrast(Document *document);
  virtual ~BrightnessAndConstrast() = default;

public slots:
  void setA(float A);
  void setB(float B);

protected:
  void fillLutTables() override;

private:
  float A_;
  float B_;
};

// --- Dialog ---

/*
 *
 */

class BACConfigDialog : public OperationConfigDialog<BrightnessAndConstrast> {
public:
  explicit BACConfigDialog(Document *document, QWidget *parent = nullptr);
  virtual ~BACConfigDialog() = default;

private:
  QDoubleSpinBox a_spin_;
  QDoubleSpinBox b_spin_;
};

} // namespace imagecpp
