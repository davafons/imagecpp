#pragma once

#include <QMenu>

class SettingsMenu : public QMenu {
  Q_OBJECT
public:
  explicit SettingsMenu(QWidget *parent = nullptr);
  virtual ~SettingsMenu() = default;

signals:
  void toggleTabsView(bool toggled);

private:
  QAction *toggle_tabs_act_;
};
