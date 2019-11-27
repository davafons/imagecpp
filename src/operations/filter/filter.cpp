#include "filter.hpp"

namespace imagecpp {

Filter::Filter(Document *document) : FilterOperation(document, tr("Filter")) {}

void Filter::fillKernel() {
  kernel_ = std::vector<std::vector<int>>(3, std::vector<int>(3, 1));
}

}  // namespace imagecpp
