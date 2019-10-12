#pragma once

#include "operations/private/operationconfigdialog.hpp"
#include "operations/private/pixeloperation.hpp"

// Forward declarations
class QRadioButton;

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class Grayscale : public PixelOperation {
  Q_OBJECT

public:
  enum class Format { NTSC, PAL };

  Grayscale(Document *document, const Format &format = Format::PAL);
  virtual ~Grayscale() = default;

public slots:
  Grayscale &setFormat(const Format &format);

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
 *
 */
class GrayscaleConfigDialog : public OperationConfigDialog<Grayscale> {
public:
  GrayscaleConfigDialog(Document *document, QWidget *parent = nullptr);
  virtual ~GrayscaleConfigDialog() = default;

private:
  QRadioButton *pal_radio_;
  QRadioButton *ntsc_radio_;
};

} // namespace imagecpp
