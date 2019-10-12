#include "inverse.hpp"

#include "image/document.hpp"

namespace imagecpp {

Inverse::Inverse(Document *document) : LutOperation(document, "Inverse") {
  fillLutTables();
}

void Inverse::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = LUT_SIZE - i;
    g_lut_[i] = LUT_SIZE - i;
    b_lut_[i] = LUT_SIZE - i;
  }
}

} // namespace imagecpp
