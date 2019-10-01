#include "editmenu.hpp"

#include <QUndoStack>

EditMenu::EditMenu(QWidget *parent) : QMenu(tr("Edit"), parent) {
  createUndoActions();

  connect(undo_act_, &QAction::triggered, this, &EditMenu::undo);
  connect(redo_act_, &QAction::triggered, this, &EditMenu::redo);

  addAction(undo_act_);
  addAction(redo_act_);
}

void EditMenu::createUndoActions(const QUndoStack *undo_stack) {
  if (undo_stack) {
    undo_act_ = undo_stack->createUndoAction(this, tr("&Undo"));
    redo_act_ = undo_stack->createUndoAction(this, tr("&Redo"));
  } else {
    undo_act_ = new QAction(tr("&Undo"), this);
    redo_act_ = new QAction(tr("&Redo"), this);

    undo_act_->setDisabled(true);
    redo_act_->setDisabled(true);
  }

  undo_act_->setShortcut(QKeySequence::Undo);
  redo_act_->setShortcut(QKeySequence::Redo);
}
