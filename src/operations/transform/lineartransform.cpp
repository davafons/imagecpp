#include "lineartransform.hpp"

#include <QChartView>
#include <QLineEdit>
#include <QLineSeries>
#include <QPushButton>
#include <QSpinBox>
#include <QValueAxis>

namespace imagecpp {

/*!
 *  \class LinearTransform
 *  \brief Applies a linear transformation to an image.
 *
 *  The user can define the steps used on the transformation.
 */

/*!
 *  Construcs a LinearTransform operation object.
 */
LinearTransform::LinearTransform(Document *document)
    : LutOperation(document, "Linear transformation") {}

/*!
 *  Returns the list of steps used by the transformation.
 */
const LinearTransform::StepsList &LinearTransform::steps() const {
  return steps_;
}

/*!
 *  Sets a new list of steps.
 */
void LinearTransform::setSteps(std::map<int, int> steps) {
  steps_ = steps;

  emit propertyChanged();
}

/*!
 *  Adds a new step to the transformation.
 */
void LinearTransform::addStep(int in, int out) {
  steps_[in] = out;

  emit propertyChanged();
}

/*!
 *  Removes a step from the transformation. The deleted key must have the value "in". If
 *  the step isn't on the list, nothing will be deleted (but the propertyChanged signal
 *  will be triggered).
 */
void LinearTransform::removeStep(int in) {
  steps_.erase(in);

  emit propertyChanged();
}

/*!
 *  Implementation of the linear transform.
 *
 *  Iterate through all steps. Calculate the equation for the rect between the two steps
 *  and fill the lut table on the corresponding range.
 */
void LinearTransform::fillLutTablesImpl() {
  // TODO: Clean

  auto lut_values_range = [this](int x_i, int y_i, int x_f, int y_f) {
    float m = 0;

    if (x_f - x_i > 0) {
      m = float(y_f - y_i) / (x_f - x_i);
    }

    int n = y_i - m * x_i;

    for (int vin = x_i; vin <= x_f; ++vin) {
      r_lut_[vin] = m * vin + n;
      g_lut_[vin] = m * vin + n;
      b_lut_[vin] = m * vin + n;
    }
  };

  // From zero to first step
  int x_i = 0;
  int y_i = 0;

  int x_f = steps_.begin()->first;
  int y_f = steps_.begin()->second;

  lut_values_range(x_i, y_i, x_f, y_f);

  // From first step to last step
  for (auto it = std::next(steps_.cbegin()); it != steps_.cend(); ++it) {
    x_i = x_f;
    y_i = y_f;

    x_f = it->first;
    y_f = it->second;

    lut_values_range(x_i, y_i, x_f, y_f);
  }

  // From last step to 255
  x_i = x_f;
  y_i = y_f;

  x_f = 255;
  y_f = 255;

  lut_values_range(x_i, y_i, x_f, y_f);
}

}  // namespace imagecpp
