#pragma once

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSpacerItem>
#include <QUndoCommand>
#include <QVBoxLayout>

#include "operations/imageoperation.hpp"
#include "widgets/image/imagedisplayarea.hpp"

class QLayout;

class ToGrayscaleOperation : public ImageOperation {
  Q_OBJECT
public:
  enum class Format { NTSC, PAL };

  ToGrayscaleOperation(ImageData *data, const Format &format = Format::PAL);

public slots:
  ToGrayscaleOperation &setFormat(const Format &format);

protected:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const override;

private:
  Format format_;

  float red_factor_{0};
  float green_factor_{0};
  float blue_factor_{0};
};

static QUndoCommand *toGrayscaleCommandDialog(ImageData *data) {
  class SettingsDialog : public QDialog {
  public:
    SettingsDialog(ImageData *data, QWidget *parent = nullptr)
        : QDialog(parent), operation_(data) {
      display_ = new ImageDisplayArea();
      display_->onImageOpened(operation_.preview());
      connect(&operation_, &ImageOperation::imageChanged, display_,
              &ImageDisplayArea::onImageUpdated);

      layout_ = new QVBoxLayout();

      QGroupBox *group_box = new QGroupBox("Format");
      pal_radio_ = new QRadioButton("PAL");
      ntsc_radio_ = new QRadioButton("NTSC");

      QVBoxLayout *vbox = new QVBoxLayout();
      vbox->addWidget(pal_radio_);
      vbox->addWidget(ntsc_radio_);
      vbox->addSpacerItem(new QSpacerItem(200, 400));
      group_box->setLayout(vbox);

      layout_->addWidget(group_box);

      QDialogButtonBox *button_box =
          new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

      layout_->addWidget(button_box);

      pal_radio_->setChecked(true);

      connect(pal_radio_, &QRadioButton::toggled, &operation_, [this] {
        operation_.setFormat(ToGrayscaleOperation::Format::PAL);
      });

      connect(ntsc_radio_, &QRadioButton::toggled, &operation_, [this] {
        operation_.setFormat(ToGrayscaleOperation::Format::NTSC);
      });

      connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
      connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);

      QHBoxLayout *true_layout = new QHBoxLayout();
      true_layout->addWidget(display_);
      true_layout->addLayout(layout_);

      setLayout(true_layout);
    }

    QUndoCommand *command() { return operation_.command(); }

  private:
    QRadioButton *pal_radio_;
    QRadioButton *ntsc_radio_;

    QLayout *layout_;

    ToGrayscaleOperation operation_;

    ImageDisplayArea *display_;
  };

  SettingsDialog dialog(data);
  dialog.exec();

  // If invalid, throw exception

  return dialog.command();
}
