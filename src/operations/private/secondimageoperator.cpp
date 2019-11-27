#include "secondimageoperator.hpp"

namespace imagecpp {

const Image* SecondImageOperator::image() const {
  return second_image_;
}

void SecondImageOperator::setImage(const Image* image) {
  second_image_ = image;

  emit imageChanged(second_image_);
}

}  // namespace imagecpp
