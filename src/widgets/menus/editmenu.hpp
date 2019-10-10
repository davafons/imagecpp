#pragma once

#include <QMenu>

// Forward declarations
class QUndoGroup;

namespace imagecpp {

/*
 */
class EditMenu : public QMenu {
  Q_OBJECT

public:
  explicit EditMenu(QWidget *parent = nullptr);
  virtual ~EditMenu() = default;

signals:
  void undo();
  void redo();

public slots:
  void createUndoActions(const QUndoGroup *undo_group = nullptr);

private:
  QAction *undo_act_;
  QAction *redo_act_;
};

} // namespace imagecpp
