#pragma once

#include "imagedifference.hpp"
#include "operations/private/imageoperationdialog.hpp"

namespace imagecpp {

class ImageDifferenceDialog : public ImageOperationDialog<ImageDifference> {
  Q_OBJECT

public:
  explicit ImageDifferenceDialog(Document *document, QWidget *parent = nullptr);

private:
};

}  // namespace imagecpp
