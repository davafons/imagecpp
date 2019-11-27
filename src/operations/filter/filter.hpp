#pragma once

#include "operations/private/filteroperation.hpp"

namespace imagecpp {
class Filter : public FilterOperation {
public:
  explicit Filter(Document* document);
  virtual ~Filter() = default;

  virtual void fillKernel() override;
};

}  // namespace imagecpp
