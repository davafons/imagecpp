#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class LutOperation : public PointOperation {
public:
  explicit LutOperation(Document *document, const QString &name = "");
  virtual ~LutOperation() = default;

protected:
  virtual void imageOperationImpl(Image *new_image) override;
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) const override;

  virtual void fillLutTablesImpl() = 0;

protected:
  static const int LUT_SIZE = 256;

  std::array<int, LUT_SIZE> r_lut_;
  std::array<int, LUT_SIZE> g_lut_;
  std::array<int, LUT_SIZE> b_lut_;
};

}  // namespace imagecpp
