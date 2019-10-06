#pragma once

#include <QMenu>

class WindowsMenu : public QMenu {
  Q_OBJECT

public:
  explicit WindowsMenu(QWidget *parent = nullptr);
  virtual ~WindowsMenu() = default;

signals:
  void toggleHistoryWindow(bool toggled);

private:
  QAction *toggle_history_w_act_;
};
