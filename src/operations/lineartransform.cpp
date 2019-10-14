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

  connect(add_button_, &QPushButton::clicked, this,
          &LinearTransformConfigDialog::addNextEmptyStep);
}

void LinearTransformConfigDialog::addStep(int in, int out) {
  operation_.addStep(in, out);

  InOutItem *step = new InOutItem(operation_.steps(), in, out);
  connect(step, &InOutItem::itemDeleted, this,
          &LinearTransformConfigDialog::removeStep);

  connect(step, &InOutItem::inModified, this,
          &LinearTransformConfigDialog::inModified);

  steps_list_layout_->insertWidget(in, step);

  qDebug() << "New index: " << steps_list_layout_->indexOf(step);

  // Lista de InoutItems (QVector<InOutItem*> items)
  // Al insertar uno:
  // Insertar en la lista.
  // Para el layout:
  // Comparar el in del objeto con el de cada item. Si se se encuentra un item tal que
  // in < item.in, significa que el objeto va insertado justo detrás de item. Utilizar
  // layout->indexof(item) para saber su posición y layout->insertWidget(pos - 1, ) para
  // insertarlo
  //
  // Al modificar uno:
  // Borrar SOLO DEL LAYOUT (no de la lista) y reinsertar en el layout ordenado (utilizando el método anterior)
  //
  // Al borrar uno:
  // Borrar de la lista y del layout
  //
  // Para obtener una lista usable:
  // Iterar todos los elementos de la lista y construir un array de 256 con el valor de
  // vout correspondiente para cada índice, o devolver un set o algo parecido.
  //
  // TODO: Pensar como evitar que en Vin se escriban valores que ya están repetidos en
  // otros elementos de la lista
}

void LinearTransformConfigDialog::removeStep(InOutItem *inout) {
  operation_.removeStep(inout->in());
  steps_list_layout_->removeWidget(inout);
}

void LinearTransformConfigDialog::inModified(InOutItem *inout) {
  int in = inout->in();
  int out = inout->out();

  qDebug() << "Old index: " << steps_list_layout_->indexOf(inout);

  steps_list_layout_->removeWidget(inout);
  steps_list_layout_->insertWidget(in, inout);
}

void LinearTransformConfigDialog::addNextEmptyStep() {
  for (int i = 0; i < 256; ++i) {
    if (!operation_.steps().count(i)) {
      addStep(i, i);
      break;
    }
  }
}

} // namespace imagecpp
