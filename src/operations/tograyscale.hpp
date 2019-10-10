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
#include "operations/imageoperationdialog.hpp"
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

class ToGrayscaleDialog : public ImageOperationDialog<ToGrayscaleOperation> {
public:
  ToGrayscaleDialog(ImageData *data, QWidget *parent = nullptr)
      : ImageOperationDialog(data, parent) {}

  virtual void setupLayoutWidgets() override {
    QGroupBox *group_box = new QGroupBox("Format");
    QVBoxLayout *vbox = new QVBoxLayout();

    pal_radio_ = new QRadioButton("PAL");
    ntsc_radio_ = new QRadioButton("NTSC");

    pal_radio_->setChecked(true);

    vbox->addWidget(pal_radio_);
    vbox->addWidget(ntsc_radio_);
    vbox->addSpacerItem(new QSpacerItem(200, 400));
    group_box->setLayout(vbox);

    settings_layout_->addWidget(group_box);

    connect(pal_radio_, &QRadioButton::toggled, &operation_, [this] {
      operation_.setFormat(ToGrayscaleOperation::Format::PAL);
    });

    connect(ntsc_radio_, &QRadioButton::toggled, &operation_, [this] {
      operation_.setFormat(ToGrayscaleOperation::Format::NTSC);
    });
  }

private:
  QRadioButton *pal_radio_;
  QRadioButton *ntsc_radio_;
};
