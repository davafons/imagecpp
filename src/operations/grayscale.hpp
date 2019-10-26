#pragma once

#include "operations/private/operationconfigdialog.hpp"
#include "operations/private/pixeloperation.hpp"

class QRadioButton;

namespace imagecpp {

class Grayscale : public PixelOperation {
  Q_OBJECT

public:
  enum class Format { NTSC, PAL };

public:
  explicit Grayscale(Document *document);
  virtual ~Grayscale() = default;

  Format format() const;

public slots:
  Grayscale &setFormat(const Format &format);

protected:
  virtual QRgb pixelOperationImpl(int x, int y, QRgb color) const override;

private:
  Format format_;

  float red_factor_{0.0f};
  float green_factor_{0.0f};
  float blue_factor_{0.0f};
};

/*!
 *
 *
 *
 *
 *
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

}  // namespace imagecpp
