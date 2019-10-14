#include "lineartransform.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

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

void LinearTransform::addStep(int in, int out) {
  steps_[in] = out;
  emit propertyChanged();
}

void LinearTransform::removeStep(int in) {
  steps_.erase(in);
  emit propertyChanged();
}

void LinearTransform::setSteps(std::map<int, int> steps) {
  steps_ = steps;
  // emit propertyChanged();
}

// --- Dialog ---

Step::Step(int in, int out, QWidget *parent) : QWidget(parent) {

  // Layout representing a label - edit - label - edit row
  QHBoxLayout *hbox = new QHBoxLayout();

  in_edit_ = new QSpinBox();
  in_edit_->setRange(0, 255);
  in_edit_->setValue(in);

  out_edit_ = new QSpinBox();
  out_edit_->setRange(0, 255);
  out_edit_->setValue(out);

  remove_button_ = new QPushButton(tr("Remove"));

  // Adding to layout
  hbox->addWidget(new QLabel(tr("In")));
  hbox->addWidget(in_edit_);
  hbox->addWidget(new QLabel(tr("Out")));
  hbox->addWidget(out_edit_);
  hbox->addWidget(remove_button_);

  // Remove from layout when clicking on remove button
  connect(remove_button_, &QPushButton::clicked, this, [this] {
    setParent(nullptr);
    emit stepRemoved(this);
  });

  connect(in_edit_, qOverload<int>(&QSpinBox::valueChanged), this,
          [this] { emit inModified(this); });
  connect(out_edit_, qOverload<int>(&QSpinBox::valueChanged), this,
          [this] { emit outModified(this); });

  // Set final layout of the widget
  setLayout(hbox);
}

LinearTransformConfigDialog::LinearTransformConfigDialog(Document *document,
                                                         QWidget *parent)
    : OperationConfigDialog(document, parent), steps_layout_(new QVBoxLayout()),
      add_button_(new QPushButton(tr("Add new step"))) {

  steps_layout_->setAlignment(Qt::AlignTop);

  settings_layout_->addLayout(steps_layout_);
  settings_layout_->addWidget(add_button_);

  addNewStep(0, 0);
  addNewStep(255, 255);

  connect(add_button_, &QPushButton::clicked, this,
          &LinearTransformConfigDialog::addNextEmptyStep);
}

// Lista de InoutItems (QVector<InOutItem*> items)
// Al insertar uno:
// Insertar en la lista.
// Para el layout:
// Comparar el in del objeto con el de cada item. Si se se encuentra un item
// tal que in < item.in, significa que el objeto va insertado justo detrás de
// item. Utilizar layout->indexof(item) para saber su posición y
// layout->insertWidget(pos - 1, ) para insertarlo
//
// Al modificar uno:
// Borrar SOLO DEL LAYOUT (no de la lista) y reinsertar en el layout ordenado
// (utilizando el método anterior)
//
// Al borrar uno:
// Borrar de la lista y del layout
//
// Para obtener una lista usable:
// Iterar todos los elementos de la lista y construir un array de 256 con el
// valor de vout correspondiente para cada índice, o devolver un set o algo
// parecido.
//
// TODO: Pensar como evitar que en Vin se escriban valores que ya están
// repetidos en otros elementos de la lista

void LinearTransformConfigDialog::addNewStep(int in, int out) {
  Step *step = new Step(in, out);

  // Make connections between the step and the list
  connect(step, &Step::stepRemoved, this,
          &LinearTransformConfigDialog::removeStep);

  connect(step, &Step::inModified, this,
          &LinearTransformConfigDialog::inModified);

  connect(step, &Step::outModified, this,
          &LinearTransformConfigDialog::outModified);

  // Add to layout. Must be ordered
  insertStepOrderedInLayout(step);

  // Add to list of widgets
  steps_list_.append(step);

  qDebug() << "New step" << in << " " << out;

  updateSteps();
}

void LinearTransformConfigDialog::removeStep(Step *step) {
  // Remove from list and layout, permanently
  steps_list_.removeOne(step);
  steps_layout_->removeWidget(step);

  updateSteps();
}

void LinearTransformConfigDialog::inModified(Step *step) {
  // Reposition widget on layout, ordered
  // qDebug() << step->in() << step->out() << "Modified";

  // int count = 0;
  // for (const auto &s : steps_list_) {
  //   if (s->in() == step->in()) {
  //     ++count;
  //   }
  // }
  //
  // // Find next gap
  //
  // if (count > 1) {
  //   int gap = findNextGap(step);
  //
  //   if (gap == -1) {
  //     step->setIn(step->in() - 1);
  //   }
  //
  //   step->setIn(gap);
  // }

  steps_layout_->removeWidget(step);
  insertStepOrderedInLayout(step);

  updateSteps();
}

void LinearTransformConfigDialog::updateSteps() {
  operation_.setSteps(generateMap());
}

void LinearTransformConfigDialog::outModified(Step *step) { updateSteps(); }

std::map<int, int> LinearTransformConfigDialog::generateMap() {
  std::map<int, int> steps_map;

  for (const auto &step : steps_list_) {
    steps_map[step->in()] = step->out();
  }

  qDebug() << "Set new map" << steps_map;

  return steps_map;
}

void LinearTransformConfigDialog::addNextEmptyStep() {
  if (steps_list_.size() == 256) {
    qDebug() << "Can't add more steps";
    // TODO: Popup?
  }

  for (int i = 0; i < 256; ++i) {
    bool found = false;
    for (const auto &pair : steps_list_) {
      if (i == pair->in()) {
        found = true;
      }
    }

    if (!found) {
      addNewStep(i, i);
      break;
    }
  }

  updateSteps();
}

void LinearTransformConfigDialog::insertStepOrderedInLayout(Step *step) {
  // Insert ordered on layout
  int index = -1;
  int closest_step = -1;
  for (const auto &s : steps_list_) {
    if (s->in() < step->in() && s->in() > closest_step) {
      closest_step = s->in();
      index = steps_layout_->indexOf(s);
    }
  }

  // Add to layout
  steps_layout_->insertWidget(index + 1, step);
}

// int LinearTransformConfigDialog::findNextGap(Step *step) {
//   for (int i = step->in() + 1; i < 256; ++i) {
//     bool found = false;
//     for (const auto &s : steps_list_) {
//       if (s->in() == i) {
//         found = true;
//       }
//     }
//
//     if (!found) {
//       return i;
//     }
//   }
//
//   return -1;
// }

} // namespace imagecpp
