#include "filterdialog.hpp"

#include <QPlainTextEdit>

namespace imagecpp {

FilterDialog::FilterDialog(Document *document, QWidget *parent)
    : ImageOperationDialog<Filter>(document, parent) {

  kernel_text_edit_ = new QPlainTextEdit();
  kernel_text_edit_->setPlainText(QString::fromStdString(operation().kernelString()));
  compile_button_ = new QPushButton("Compile Kernel");

  connect(compile_button_, &QPushButton::clicked, this, [this]() {
    operation().setKernelFromString(kernel_text_edit_->toPlainText().toStdString());
  });

  settings_layout_->addWidget(kernel_text_edit_);
  settings_layout_->addWidget(compile_button_);
}

}  // namespace imagecpp
