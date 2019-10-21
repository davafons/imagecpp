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
  void setStd(float target_std);
  void setMean(float target_mean);

  void setA(float A);
  void setA(float red_A, float green_A, float blue_A);

  void setB(float B);
  void setB(float red_B, float green_B, float blue_B);

  void setRedA(float A);
  void setRedB(float B);

  void setGreenA(float A);
  void setGreenB(float B);

  void setBlueA(float A);
  void setBlueB(float B);

protected:
  void fillLutTables() override;

private:
  struct Params {
    float A = 1.0f;
    float B = 0.0f;
  };

  Params red_;
  Params green_;
  Params blue_;
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
