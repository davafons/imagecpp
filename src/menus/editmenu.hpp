#pragma once

#include <QMenu>

class QUndoStack;

class EditMenu : public QMenu {
  Q_OBJECT

public:
  explicit EditMenu(QWidget *parent = nullptr);
  virtual ~EditMenu() = default;

signals:
  void undo();
  void redo();

public slots:
  void createUndoActions(const QUndoStack *undo_stack = nullptr);

private:
  QAction *undo_act_;
  QAction *redo_act_;
};
