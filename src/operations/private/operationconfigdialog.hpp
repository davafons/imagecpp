#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "operations/private/imageoperation.hpp"
#include "widgets/image/imagedisplayarea.hpp"
#include "image/document.hpp"

namespace imagecpp {

/*
 *
 */
template <class OperationType> class OperationConfigDialog : public QDialog {
public:
  OperationConfigDialog(Document *data, QWidget *parent);
  virtual ~OperationConfigDialog() { delete preview_display_; }

  QUndoCommand *command() { return operation_.command(); }

protected:
  OperationType operation_;

  QVBoxLayout *settings_layout_;
  QDialogButtonBox *button_box_;

private:
  ImageDisplayArea *preview_display_;
};

template <class OperationType>
OperationConfigDialog<OperationType>::OperationConfigDialog(Document *data,
                                                            QWidget *parent)
    : QDialog(parent), operation_(data),
      preview_display_(new ImageDisplayArea()),
      settings_layout_(new QVBoxLayout()),
      button_box_(new QDialogButtonBox(QDialogButtonBox::Ok |
                                       QDialogButtonBox::Cancel)) {

  // Setup widgets
  preview_display_->onImageOpened(operation_.preview());

  // Create main layout (Left - Preview, Right - Operation config)
  QHBoxLayout *dialog_layout = new QHBoxLayout();
  dialog_layout->addWidget(preview_display_);

  // Create right side layout (Up - config, Down - Realtime checkbox, Ok/Cancel
  // buttons)
  QVBoxLayout *temp_vbox = new QVBoxLayout();
  temp_vbox->addLayout(settings_layout_);

  QCheckBox *liveupdate_checkbox = new QCheckBox(tr("Realtime"));
  liveupdate_checkbox->setChecked(operation_.isLiveUpdateActive());
  temp_vbox->addWidget(liveupdate_checkbox);

  temp_vbox->addWidget(button_box_);

  dialog_layout->addLayout(temp_vbox);

  // Set main layout to dialog
  setLayout(dialog_layout);

  // If the image is changed, update the preview
  connect(&operation_, &ImageOperation::imageUpdated, preview_display_,
          &ImageDisplayArea::onImageUpdated);

  // Connect the liveupdate checkbox with the property of the operation object
  connect(liveupdate_checkbox, &QCheckBox::stateChanged, &operation_,
          &ImageOperation::toggleLiveUpdate);
  // Show/hide the preview panel when the liveupdate checkbox if toggled
  connect(liveupdate_checkbox, &QCheckBox::stateChanged, preview_display_,
          &ImageDisplayArea::setVisible);

  // Connect Accept/Cancel buttons
  connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

} // namespace imagecpp
