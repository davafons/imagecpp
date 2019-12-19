#pragma once

#include "operations/private/filteroperation.hpp"

namespace imagecpp {
class Filter : public FilterOperation {
public:
  explicit Filter(Document* document);
  virtual ~Filter() = default;

  virtual void fillKernel() override;

  std::string kernelString() const;

  void setKernelFromString(const std::string& kernel_str);

private:
  std::string kernel_str_ = "";
};

}  // namespace imagecpp
