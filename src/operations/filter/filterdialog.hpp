#pragma once

#include "filter.hpp"
#include "operations/private/imageoperationdialog.hpp"

class QPlainTextEdit;
class QPushButton;

namespace imagecpp {

class FilterDialog : public ImageOperationDialog<Filter> {
  Q_OBJECT
public:
  explicit FilterDialog(Document *document, QWidget *parent = nullptr);

private:
  QPlainTextEdit *kernel_text_edit_{nullptr};
  QPushButton *compile_button_{nullptr};
};

}  // namespace imagecpp
