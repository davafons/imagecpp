#pragma once

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class Inverse : public LutOperation {
  Q_OBJECT

public:
  Inverse(Document *document);
  virtual ~Inverse() = default;

protected slots:
  void fillLutTables() override;
};

} // namespace imagecpp
