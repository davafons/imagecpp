#include "lineartransform.hpp"

namespace imagecpp {

// --- Implementation ---

LinearTransform::LinearTransform(Document *document,
                                 const std::set<Pair> &steps)
    : LutOperation(document, "Linear Transformation"), steps_(steps) {
  fillLutTables();
}

void LinearTransform::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = LUT_SIZE - i;
    g_lut_[i] = LUT_SIZE - i;
    b_lut_[i] = LUT_SIZE - i;
  }
}

void LinearTransform::addStep(int in, int out) { steps_.insert(Pair(in, out)); }

// --- Dialog ---

LinearTransformConfigDialog::LinearTransformConfigDialog(Document *document,
                                                         QWidget *parent)
    : OperationConfigDialog(document, parent) {}

} // namespace imagecpp
