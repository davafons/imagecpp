#pragma once

#include <QDoubleSpinBox>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

namespace imagecpp {

class GammaCorrection : public LutOperation {
  Q_OBJECT

public:
  GammaCorrection(Document *document);
  virtual ~GammaCorrection() = default;

public slots:
  void setGamma(float gamma);

protected slots:
  virtual void fillLutTables() override;

private:
  float gamma_{1.0f};
};

class GammaCorrectionConfigDialog
    : public OperationConfigDialog<GammaCorrection> {
public:
  explicit GammaCorrectionConfigDialog(Document *document,
                                       QWidget *parent = nullptr);
  virtual ~GammaCorrectionConfigDialog() = default;

private:
  QDoubleSpinBox gamma_spin_;
};

} // namespace imagecpp
