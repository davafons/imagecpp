#pragma once

#include <QDebug>

#include "operations/imageoperation.hpp"

class ToGrayscaleCommand : public ImageOperation {

public:
  enum class Format { NTSC, PAL };

  ToGrayscaleCommand(ImageData *data);

protected:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const override;

private:
  float red_factor_{0};
  float green_factor_{0};
  float blue_factor_{0};
};
