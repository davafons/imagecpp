#include "editmenu.hpp"

#include <QDebug>
#include <QUndoGroup>

namespace imagecpp {

EditMenu::EditMenu(QWidget *parent) : QMenu(tr("Edit"), parent) {
  createUndoActions();

  rect_select_act_ = new QAction(tr("%Rectangular selection"), this);
  rect_select_act_->setStatusTip(
      tr("Select a rectangular portion of the image"));

  connect(rect_select_act_, &QAction::triggered, this, &EditMenu::rectSelect);

  // Menu layout

  addAction(undo_act_);
  addAction(redo_act_);
  addSeparator();
  addAction(rect_select_act_);
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

} // namespace imagecpp
