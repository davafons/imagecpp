#include "settingsmenu.hpp"

#include <QDebug>
#include <QKeySequence>

namespace imagecpp {

SettingsMenu::SettingsMenu(QWidget *parent) : QMenu(tr("Settings"), parent) {

  toggle_tabs_act_ = new QAction(tr("View as tabs instead of windows"), this);
  toggle_tabs_act_->setCheckable(true);
  toggle_tabs_act_->setChecked(false);

  toggle_tabs_act_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));

  connect(toggle_tabs_act_, &QAction::triggered, this,
          &SettingsMenu::toggleTabsView);

  addAction(toggle_tabs_act_);
}

} // namespace imagecpp
