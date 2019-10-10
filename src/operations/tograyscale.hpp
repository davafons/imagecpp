#pragma once

#include "operations/private/imageoperation.hpp"
#include "operations/private/imageoperationdialog.hpp"

// Forward declarations
class QRadioButton;

namespace imagecpp {

// --- Implementation ---

/*
 */
class ToGrayscaleOperation : public ImageOperation {
  Q_OBJECT

public:
  enum class Format { NTSC, PAL };

  ToGrayscaleOperation(Document *data, const Format &format = Format::PAL);
  virtual ~ToGrayscaleOperation() = default;

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

// --- Dialog ---

/*
 */
class ToGrayscaleDialog : public ImageOperationDialog<ToGrayscaleOperation> {
public:
  ToGrayscaleDialog(Document *data, QWidget *parent = nullptr);
  virtual ~ToGrayscaleDialog() = default;

private:
  QRadioButton *pal_radio_;
  QRadioButton *ntsc_radio_;
};

} // namespace imagecpp
