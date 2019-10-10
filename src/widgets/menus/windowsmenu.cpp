#include "windowsmenu.hpp"

#include <QDebug>
#include <QKeySequence>

namespace imagecpp {

WindowsMenu::WindowsMenu(QWidget *parent) : QMenu(tr("Windows"), parent) {

  toggle_history_w_act_ = new QAction(tr("History window"), this);
  toggle_history_w_act_->setCheckable(true);
  toggle_history_w_act_->setChecked(true);

  toggle_history_w_act_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));

  connect(toggle_history_w_act_, &QAction::triggered, this,
          &WindowsMenu::toggleHistoryWindow);

  addAction(toggle_history_w_act_);
}

} // namespace imagecpp
