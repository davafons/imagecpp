#pragma once

#include <QDoubleSpinBox>

#include "operations/private/lutoperation.hpp"

namespace imagecpp {

class GammaCorrection : public LutOperation {
  Q_OBJECT

public:
  explicit GammaCorrection(Document *document);
  virtual ~GammaCorrection() = default;

  float gamma() const;

public slots:
  void setGamma(float gamma);

protected:
  virtual void fillLutTablesImpl() override;

private:
  float gamma_{1.0f};
};

}  // namespace imagecpp
