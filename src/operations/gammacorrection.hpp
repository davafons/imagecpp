#pragma once

#include <QDoubleSpinBox>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

namespace imagecpp {

class GammaCorrection : public LutOperation {
  Q_OBJECT

public:
  explicit GammaCorrection(Document *document);
  virtual ~GammaCorrection() = default;

  float gamma() const;

public slots:
  // TODO: Return reference to same
  void setGamma(float gamma);

protected:
  virtual void fillLutTablesImpl() override;

private:
  float gamma_{1.0f};
};

/*!
 *
 *
 *
 *
 *
 *
 */
class GammaCorrectionConfigDialog : public OperationConfigDialog<GammaCorrection> {
public:
  explicit GammaCorrectionConfigDialog(Document *document, QWidget *parent = nullptr);
  virtual ~GammaCorrectionConfigDialog() = default;

private:
  QDoubleSpinBox gamma_spin_;
};

}  // namespace imagecpp
