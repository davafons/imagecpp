#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "image/document.hpp"
#include "image/histogramview.hpp"
#include "operations/private/imageoperation.hpp"
#include "widgets/image/imagedisplayarea.hpp"

namespace imagecpp {

/*
 *
 */
template <class OpType>
class ImageOperationDialog : public QDialog {
public:
  explicit ImageOperationDialog(Document *document, QWidget *parent = nullptr);
  virtual ~ImageOperationDialog() = default;

  QUndoCommand *command() { return operation_.command(); }
  OpType &operation() { return operation_; }

private:
  void addConnections();
  void configureWidgets();
  void setupLayout();

protected:
  QVBoxLayout *settings_layout_{nullptr};

  ImageDisplayArea *preview_display_{nullptr};

private:
  OpType operation_;

  QCheckBox *image_rtupdate_checkbox_{nullptr};

  QPushButton *old_histogram_button_{nullptr};
  QPushButton *new_histogram_button_{nullptr};

  QDialogButtonBox *button_box_{nullptr};

  QDialog *old_histogram_dialog_{nullptr};
  QDialog *new_histogram_dialog_{nullptr};
};

template <class OpType>
ImageOperationDialog<OpType>::ImageOperationDialog(Document *document, QWidget *parent)
    : QDialog(parent), operation_(document) {

  settings_layout_ = new QVBoxLayout();

  preview_display_ = new ImageDisplayArea();
  image_rtupdate_checkbox_ = new QCheckBox(tr("Preview image"));
  old_histogram_button_ = new QPushButton(tr("Original histogram"));
  new_histogram_button_ = new QPushButton(tr("New histogram"));
  button_box_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  old_histogram_dialog_ = new QDialog(this);
  new_histogram_dialog_ = new QDialog(this);

  configureWidgets();
  addConnections();
  setupLayout();
}

template <class OpType>
void ImageOperationDialog<OpType>::addConnections() {
  // Preview widget
  connect(&operation_,
          &ImageOperation::newImageGenerated,
          preview_display_,
          &ImageDisplayArea::onImageUpdated);

  connect(preview_display_,
          &ImageDisplayArea::selectionCreated,
          &operation_,
          &ImageOperation::setSelection);

  // Realtime checkbox
  connect(image_rtupdate_checkbox_,
          &QCheckBox::stateChanged,
          &operation_,
          &ImageOperation::toggleImageRealtimeUpdate);

  connect(image_rtupdate_checkbox_,
          &QCheckBox::stateChanged,
          preview_display_,
          &ImageDisplayArea::setVisible);

  // Histogram buttons
  connect(new_histogram_button_,
          &QPushButton::clicked,
          &operation_,
          &ImageOperation::toggleHistogramRealtimeUpdate);

  connect(new_histogram_button_,
          &QPushButton::clicked,
          new_histogram_dialog_,
          &QDialog::setVisible);

  connect(old_histogram_button_,
          &QPushButton::clicked,
          old_histogram_dialog_,
          &QDialog::setVisible);

  // Button box
  connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

template <class OpType>
void ImageOperationDialog<OpType>::configureWidgets() {
  preview_display_->onImageOpened(operation_.newImage());

  image_rtupdate_checkbox_->setChecked(operation_.isImageRealtimeUpdateToggled());

  old_histogram_button_->setCheckable(true);
  old_histogram_button_->setChecked(false);

  new_histogram_button_->setCheckable(true);
  new_histogram_button_->setChecked(false);

  // Old histogram

  old_histogram_dialog_->setWindowTitle(tr("Histogram of original image"));

  HistogramView *old_histogram_view = new HistogramView();
  old_histogram_view->setHistogram(&operation_.oldHistogram());

  QVBoxLayout *old_histogram_layout = new QVBoxLayout();
  old_histogram_layout->addWidget(old_histogram_view);

  old_histogram_dialog_->setLayout(old_histogram_layout);

  // New histogram

  new_histogram_dialog_->setWindowTitle(tr("Histogram of new image"));

  HistogramView *new_histogram_view = new HistogramView();
  new_histogram_view->setHistogram(&operation_.newHistogram());

  QVBoxLayout *new_histogram_layout = new QVBoxLayout();
  new_histogram_layout->addWidget(new_histogram_view);

  new_histogram_dialog_->setLayout(new_histogram_layout);

  connect(&operation_.newHistogram(),
          &Histogram::histogramChanged,
          new_histogram_view,
          &HistogramView::setHistogram);
}

template <class OpType>
void ImageOperationDialog<OpType>::setupLayout() {

  QHBoxLayout *histogram_buttons_layout = new QHBoxLayout();
  histogram_buttons_layout->addWidget(new_histogram_button_);
  histogram_buttons_layout->addWidget(old_histogram_button_);

  QVBoxLayout *settings_and_extra_layout = new QVBoxLayout();
  settings_and_extra_layout->addLayout(settings_layout_);
  settings_and_extra_layout->addWidget(image_rtupdate_checkbox_);
  settings_and_extra_layout->addLayout(histogram_buttons_layout);
  settings_and_extra_layout->addWidget(button_box_);

  QHBoxLayout *dialog_layout = new QHBoxLayout();
  dialog_layout->addWidget(preview_display_);
  dialog_layout->addLayout(settings_and_extra_layout);

  setLayout(dialog_layout);
}

// {
//
//   // Setup widgets
//   preview_display_->onImageOpened(operation_.newImage());
//
//   // Create main layout (Left - Preview, Right - Operation config)
//   QHBoxLayout *dialog_layout = new QHBoxLayout();
//   dialog_layout->addWidget(preview_display_);
//
//   // Create right side layout (Up - config, Down - Realtime checkbox, Ok/Cancel
//   // buttons)
//   QVBoxLayout *temp_vbox = new QVBoxLayout();
//   temp_vbox->addLayout(settings_layout_);
//
//   QCheckBox *liveupdate_checkbox = new QCheckBox(tr("Realtime update"));
//   liveupdate_checkbox->setChecked(operation_.isImageRealtimeUpdateToggled());
//   temp_vbox->addWidget(liveupdate_checkbox);
//
//   QCheckBox *histogram_liveupdate_checkbox = new QCheckBox(tr("Histogram"));
//   histogram_liveupdate_checkbox->setChecked(
//       operation_.isHistogramRealtimeUpdateToggled());
//
//   temp_vbox->addWidget(histogram_liveupdate_checkbox);
//
//   temp_vbox->addWidget(button_box_);
//
//   dialog_layout->addLayout(temp_vbox);
//
//   // Set main layout to dialog
//   setLayout(dialog_layout);
//
//   // If the image is changed, update the preview
//   connect(&operation_,
//           &ImageOperation::newImageGenerated,
//           preview_display_,
//           &ImageDisplayArea::onImageUpdated);
//
//   // Connect the liveupdate checkbox with the property of the operation object
//   connect(liveupdate_checkbox,
//           &QCheckBox::stateChanged,
//           &operation_,
//           &ImageOperation::toggleImageRealtimeUpdate);
//
//   // Show/hide the preview panel when the liveupdate checkbox if toggled
//   connect(liveupdate_checkbox,
//           &QCheckBox::stateChanged,
//           preview_display_,
//           &ImageDisplayArea::setVisible);
//
//   connect(histogram_liveupdate_checkbox,
//           &QCheckBox::stateChanged,
//           &operation_,
//           &ImageOperation::toggleHistogramRealtimeUpdate);
//
//   // Connect Accept/Cancel buttons
//   connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
//   connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
// }

}  // namespace imagecpp
