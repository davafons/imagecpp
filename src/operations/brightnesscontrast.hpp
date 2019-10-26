#pragma once

#include <QGroupBox>
#include <QSlider>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

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

/*!
 *
 *
 *
 *
 *
 *
 */

class BACConfigDialog : public OperationConfigDialog<BrightnessAndConstrast> {
  Q_OBJECT

public:
  explicit BACConfigDialog(Document *document, QWidget *parent = nullptr);
  virtual ~BACConfigDialog() = default;

private slots:
  void resetSliders();

private:
  QGroupBox general_box_;
  QSlider general_bright_slider_{Qt::Horizontal};
  QSlider general_contrast_slider_{Qt::Horizontal};

  QGroupBox rgb_bright_box_;
  QSlider red_bright_slider_{Qt::Horizontal};
  QSlider green_bright_slider_{Qt::Horizontal};
  QSlider blue_bright_slider_{Qt::Horizontal};

  QGroupBox rgb_contrast_box_;
  QSlider red_contrast_slider_{Qt::Horizontal};
  QSlider green_contrast_slider_{Qt::Horizontal};
  QSlider blue_contrast_slider_{Qt::Horizontal};

  QPushButton reset_button_{tr("Reset")};
  QPushButton more_button_{tr("More")};
};

}  // namespace imagecpp
