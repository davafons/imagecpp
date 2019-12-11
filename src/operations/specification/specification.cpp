#include "specification.hpp"

namespace imagecpp {

Specification::Specification(Document* document)
    : LutOperation(document, tr("Specification")) {}

void Specification::setSecondImage(const Image* image) {
  second_image_ = image;
  second_image_histogram_.generateHistogram(second_image_);

  emit propertyChanged();
}

void Specification::fillLutTablesImpl() {
  auto fill_lut = [this](auto& lut, const auto* p_o, const auto* p_r) {
    const int K = LUT_SIZE;

    for (int i = 0; i < K; ++i) {
      int j = K - 1;
      do {
        lut[i] = j;
        --j;
      } while (j >= 0 && p_o->at(i) <= p_r->at(j));
    }
  };

  const auto* red_p_o = oldHistogram().red().cummulativeBarsNormalized();
  const auto* red_p_r = second_image_histogram_.red().cummulativeBarsNormalized();
  fill_lut(r_lut_, red_p_o, red_p_r);

  const auto* green_p_o = oldHistogram().green().cummulativeBarsNormalized();
  const auto* green_p_r = second_image_histogram_.green().cummulativeBarsNormalized();
  fill_lut(g_lut_, green_p_o, green_p_r);

  const auto* blue_p_o = oldHistogram().blue().cummulativeBarsNormalized();
  const auto* blue_p_r = second_image_histogram_.blue().cummulativeBarsNormalized();
  fill_lut(b_lut_, blue_p_o, blue_p_r);
}

void Specification::imageOperationImpl(Image* new_image) {
  if (second_image_ == nullptr) {
    return;
  }

  LutOperation::imageOperationImpl(new_image);
}

}  // namespace imagecpp
