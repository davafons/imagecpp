#pragma once

#include "operations/private/pointoperation.hpp"

class QRadioButton;

namespace imagecpp {

class Grayscale : public PointOperation {
  Q_OBJECT

public:
  enum class Format { NTSC, PAL };

public:
  explicit Grayscale(Document *document);
  virtual ~Grayscale() = default;

  Format format() const;

public slots:
  void setFormat(const Format &format);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) const override;

private:
  Format format_;

  float red_factor_{0.0f};
  float green_factor_{0.0f};
  float blue_factor_{0.0f};
};

}  // namespace imagecpp
