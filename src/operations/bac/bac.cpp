#include "bac.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "image/document.hpp"

namespace imagecpp {

/*!
 *  \class BrightnessAndContrast
 *  \brief Transforms the brightness or constrast of an image.
 */

/*!
 *  Construcs a BrightnessAndConstrast operation object.
 */
BrightnessAndConstrast::BrightnessAndConstrast(Document *document)
    : LutOperation(document, tr("Brightness/Contrast")) {}

/*!
 *  Sets the desired standard deviation (constrast) of the image.
 *
 *  \sa setA()
 */
void BrightnessAndConstrast::setStd(float desired_std, Channel channel) {
  float red_A = desired_std / oldHistogram().red().stdev();
  float green_A = desired_std / oldHistogram().green().stdev();
  float blue_A = desired_std / oldHistogram().blue().stdev();

  switch (channel) {
    case Channel::Red:
      setA(red_A, channel);
      break;

    case Channel::Green:
      setA(green_A, channel);
      break;

    case Channel::Blue:
      setA(blue_A, channel);
      break;

    default:
    case Channel::All:
      setA(red_A, green_A, blue_A);
      break;
  }
}

void BrightnessAndConstrast::setMean(float desired_mean, Channel channel) {
  float red_B = desired_mean - red_.A * oldHistogram().red().mean();
  float green_B = desired_mean - green_.A * oldHistogram().green().mean();
  float blue_B = desired_mean - blue_.A * oldHistogram().blue().mean();

  qDebug() << red_B;

  switch (channel) {
    case Channel::Red:
      setB(red_B, channel);
      break;

    case Channel::Green:
      setB(green_B, channel);
      break;

    case Channel::Blue:
      setB(blue_B, channel);
      break;

    default:
    case Channel::All:
      setB(red_B, green_B, blue_B);
      break;
  }
}

void BrightnessAndConstrast::setA(float A, Channel channel) {
  switch (channel) {
    case Channel::Red:
      red_.A = A;
      break;

    case Channel::Green:
      green_.A = A;
      break;

    case Channel::Blue:
      blue_.A = A;
      break;

    default:
    case Channel::All:
      red_.A = A;
      green_.A = A;
      blue_.A = A;
      break;
  }

  emit propertyChanged();
}

void BrightnessAndConstrast::setA(float red_A, float green_A, float blue_A) {
  blockSignals(true);
  setA(red_A, Channel::Red);
  setA(green_A, Channel::Green);
  setA(blue_A, Channel::Blue);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float B, Channel channel) {
  switch (channel) {
    case Channel::Red:
      red_.B = B;
      break;

    case Channel::Green:
      green_.B = B;
      break;

    case Channel::Blue:
      blue_.B = B;
      break;

    default:
    case Channel::All:
      red_.B = B;
      green_.B = B;
      blue_.B = B;
      break;
  }

  emit propertyChanged();
}

void BrightnessAndConstrast::setB(float red_B, float green_B, float blue_B) {
  blockSignals(true);
  setB(red_B, Channel::Red);
  setB(green_B, Channel::Green);
  setB(blue_B, Channel::Blue);
  blockSignals(false);

  emit propertyChanged();
}

void BrightnessAndConstrast::fillLutTablesImpl() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = std::max(0.0f, std::min(red_.A * i + red_.B, 255.0f));
    g_lut_[i] = std::max(0.0f, std::min(green_.A * i + green_.B, 255.0f));
    b_lut_[i] = std::max(0.0f, std::min(blue_.A * i + blue_.B, 255.0f));
  }
}

}  // namespace imagecpp
