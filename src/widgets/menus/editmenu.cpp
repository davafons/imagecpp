#include "editmenu.hpp"

#include <QDebug>
#include <QUndoGroup>

EditMenu::EditMenu(QWidget *parent) : QMenu(tr("Edit"), parent) {
  createUndoActions();

  addAction(undo_act_);
  addAction(redo_act_);
}

void EditMenu::createUndoActions(const QUndoGroup *undo_group) {
  if (undo_group) {
    undo_act_ = undo_group->createUndoAction(this, tr("&Undo"));
    redo_act_ = undo_group->createUndoAction(this, tr("&Redo"));

  } else {
    undo_act_ = new QAction(tr("&Undo"), this);
    redo_act_ = new QAction(tr("&Redo"), this);
  }

  undo_act_->setShortcut(QKeySequence::Undo);
  redo_act_->setShortcut(QKeySequence::Redo);

  connect(undo_act_, &QAction::triggered, this, &EditMenu::undo);
  connect(redo_act_, &QAction::triggered, this, &EditMenu::redo);
}
