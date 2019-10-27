#include "imagedifferencedialog.hpp"

namespace imagecpp {

ImageDifferenceDialog::ImageDifferenceDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<ImageDifference>(document, parent) {}

}  // namespace imagecpp
