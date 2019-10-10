#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include "image/imagedata.hpp"
#include "operations/imageoperation.hpp"
#include "widgets/image/imagedisplayarea.hpp"

template <class OperationType> class ImageOperationDialog : public QDialog {
public:
  ImageOperationDialog(ImageData *data, QWidget *parent)
      : operation_(data), QDialog(parent) {
    data_ = data;
    preview_display_ = new ImageDisplayArea();
    settings_layout_ = new QVBoxLayout();
    button_box_ =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

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
  virtual ~ImageOperationDialog() { delete preview_display_; }

  virtual void setupLayoutWidgets() = 0;

  QUndoCommand *command() { return operation_.command(); }

protected:
  ImageData *data_;
  OperationType operation_;

  QVBoxLayout *settings_layout_;

private:
  ImageDisplayArea *preview_display_;
  QDialogButtonBox *button_box_;
};

template <class DialogType>
static QUndoCommand *createCommand(ImageData *data) {
  DialogType dialog(data);
  dialog.setupLayoutWidgets(); // TODO: NO me gusta pero es lo que hay

  int return_value = dialog.exec();

  if (return_value) {
    qDebug() << "Inside if" << return_value;
    return dialog.command();
  } else {
    qDebug() << "Outside if" << return_value;
    return nullptr;
  }
}
