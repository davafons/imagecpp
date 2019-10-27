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
  int x_i = steps_.begin()->first;
  int y_i = steps_.begin()->second;

  for (auto it = std::next(steps_.cbegin()); it != steps_.cend(); ++it) {
    int x_f = it->first;
    int y_f = it->second;

    int m = (y_f - y_i) / (x_f - x_i);
    int n = y_i - m * x_i;

    for (int vin = x_i; vin <= x_f; ++vin) {
      r_lut_[vin] = m * vin + n;
      g_lut_[vin] = m * vin + n;
      b_lut_[vin] = m * vin + n;
    }

    x_i = x_f;
    y_i = y_f;
  }
}

}  // namespace imagecpp
