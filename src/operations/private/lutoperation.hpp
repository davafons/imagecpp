#pragma once

#include "operations/private/pixeloperation.hpp"

namespace imagecpp {

/*
 *
 */
class LutOperation : public PixelOperation {
public:
  LutOperation(Document *document, const QString &name = "");
  virtual ~LutOperation() = default;

private:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const override;

protected:
  virtual void fillLutTables() = 0;
  virtual void generateTargetImage() override;

protected:
  static const int LUT_SIZE = 256;

  std::array<int, LUT_SIZE> r_lut_;
  std::array<int, LUT_SIZE> g_lut_;
  std::array<int, LUT_SIZE> b_lut_;
};

} // namespace imagecpp
