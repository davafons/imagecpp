#pragma once

#include <QGroupBox>
#include <QSlider>

#include "operations/private/lutoperation.hpp"

namespace imagecpp {

class BrightnessAndConstrast : public LutOperation {
  Q_OBJECT

public:
  enum class Channel { Red, Green, Blue, All };

public:
  explicit BrightnessAndConstrast(Document *document);
  virtual ~BrightnessAndConstrast() = default;

public slots:
  void setStd(float target_std, Channel channel = Channel::All);
  void setMean(float desired_mean, Channel channel = Channel::All);

  void setA(float A, Channel channel = Channel::All);
  void setA(float red_A, float green_A, float blue_A);

  void setB(float B, Channel channel = Channel::All);
  void setB(float red_B, float green_B, float blue_B);

protected:
  void fillLutTablesImpl() override;

private:
  struct BocParams {
    float A = 1.0f;
    float B = 0.0f;
  };

  BocParams red_;
  BocParams green_;
  BocParams blue_;
};

}  // namespace imagecpp
