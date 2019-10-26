#pragma once

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

namespace imagecpp {

class Inverse : public LutOperation {
  Q_OBJECT

public:
  explicit Inverse(Document *document);
  virtual ~Inverse() = default;

protected slots:
  virtual void fillLutTablesImpl() override;
};

} // namespace imagecpp
