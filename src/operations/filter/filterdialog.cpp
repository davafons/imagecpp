#include "filterdialog.hpp"

namespace imagecpp {

FilterDialog::FilterDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Filter>(document, parent) {}

}  // namespace imagecpp
