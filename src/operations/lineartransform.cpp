#include "lineartransform.hpp"

#include <QLineEdit>
#include <QPushButton>

namespace imagecpp {

// --- Implementation ---

LinearTransform::LinearTransform(Document *document,
                                 const std::map<int, int> &steps)
    : LutOperation(document, "Linear Transformation"), steps_(steps) {
  fillLutTables();
}

void LinearTransform::fillLutTables() {
  for (int i = 0; i < LUT_SIZE; ++i) {
    r_lut_[i] = LUT_SIZE - i;
    g_lut_[i] = LUT_SIZE - i;
    b_lut_[i] = LUT_SIZE - i;
  }
}

void LinearTransform::addStep(int in, int out) { steps_[in] = out; }
void LinearTransform::removeStep(int in) { steps_.erase(in); }

// --- Dialog ---

LinearTransformConfigDialog::LinearTransformConfigDialog(Document *document,
                                                         QWidget *parent)
    : OperationConfigDialog(document, parent),
      steps_list_layout_(new QVBoxLayout()),
      add_button_(new QPushButton(tr("Add new step"))) {

  steps_list_layout_->setAlignment(Qt::AlignTop);
  settings_layout_->addLayout(steps_list_layout_);

  settings_layout_->addWidget(add_button_);

  for (const auto &inout : operation_.steps()) {
    addStep(inout.first, inout.second);
  }

  connect(add_button_, &QPushButton::clicked, this, [this] { addStep(); });
}

void LinearTransformConfigDialog::addStep(int in, int out) {
  InOutItem *step = new InOutItem(in, out);

  connect(step, &InOutItem::itemDeleted, steps_list_layout_,
          &QLayout::removeWidget);

  steps_list_layout_->insertWidget(in, step);
}

} // namespace imagecpp
