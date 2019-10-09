#pragma once

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

#include "operations/imageoperation.hpp"

class QLayout;

class ToGrayscaleCreator : public QDialog {
public:
private:
};

class ToGrayscaleOperation : public ImageOperation {
  Q_OBJECT
public:
  enum class Format { NTSC, PAL };

  ToGrayscaleOperation(ImageData *data, const Format &format);

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
