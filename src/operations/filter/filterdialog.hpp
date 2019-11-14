#pragma once

#include "filter.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class FilterDialog : public ImageOperationDialog<Filter> {
  Q_OBJECT
public:
  explicit FilterDialog(Document *document, QWidget *parent = nullptr);

private:
};

}  // namespace imagecpp
