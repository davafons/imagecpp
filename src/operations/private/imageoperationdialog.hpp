#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "operations/private/imageoperation.hpp"
#include "widgets/image/imagedisplayarea.hpp"

namespace imagecpp {

template <class DialogType>
static QUndoCommand *createCommandFromDialog(Document *data) {
  DialogType dialog(data);

  int return_value = dialog.exec();

  if (return_value == QDialog::Accepted) {
    return dialog.command();
  }

  return nullptr;
}

/*
 *
 */
template <class OperationType> class ImageOperationDialog : public QDialog {
public:
  ImageOperationDialog(Document *data, QWidget *parent);
  virtual ~ImageOperationDialog() { delete preview_display_; }

  QUndoCommand *command() { return operation_.command(); }

protected:
  OperationType operation_;

  QVBoxLayout *settings_layout_;
  QDialogButtonBox *button_box_;

private:
  ImageDisplayArea *preview_display_;
};

template <class DialogType>
ImageOperationDialog<DialogType>::ImageOperationDialog(Document *data,
                                                       QWidget *parent)
    : QDialog(parent), operation_(data),
      preview_display_(new ImageDisplayArea()),
      settings_layout_(new QVBoxLayout()),
      button_box_(new QDialogButtonBox(QDialogButtonBox::Ok |
                                       QDialogButtonBox::Cancel)) {

  preview_display_->onImageOpened(operation_.preview());

  QHBoxLayout *dialog_layout = new QHBoxLayout();
  dialog_layout->addWidget(preview_display_);

  QVBoxLayout *temp_vbox = new QVBoxLayout();
  temp_vbox->addLayout(settings_layout_);
  temp_vbox->addWidget(button_box_);

  dialog_layout->addLayout(temp_vbox);

  setLayout(dialog_layout);

  connect(&operation_, &ImageOperation::imageChanged, preview_display_,
          &ImageDisplayArea::onImageUpdated);

  connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

} // namespace imagecpp
