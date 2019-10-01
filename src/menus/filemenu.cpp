#include "filemenu.hpp"

#include <QFileDialog>
#include <QUndoStack>

FileMenu::FileMenu(QWidget *parent) : QMenu(tr("File"), parent) {

  open_act_ = new QAction(tr("&Open"), this);
  open_act_->setShortcut(QKeySequence::Open);
  open_act_->setStatusTip(tr("Open an image"));

  save_act_ = new QAction(tr("&Save"), this);
  save_act_->setShortcut(QKeySequence::Save);
  save_act_->setStatusTip(tr("Save current image"));

  save_as_act_ = new QAction(tr("&Save As..."), this);
  save_as_act_->setShortcut(QKeySequence::SaveAs);
  save_as_act_->setStatusTip(tr("Save current image as a new image"));

  close_view_act_ = new QAction(tr("Close current view"), this);
  close_view_act_->setStatusTip(tr("Close current active window"));

  close_all_act_ = new QAction(tr("Close all"), this);
  close_all_act_->setStatusTip(tr("Close all open windows"));

  quit_act_ = new QAction(tr("&Quit"), this);
  quit_act_->setShortcut(QKeySequence::Quit);
  quit_act_->setStatusTip(tr("Quit from the application"));

  addSeparator();

  connect(open_act_, &QAction::triggered, this, &FileMenu::open);
  connect(save_act_, &QAction::triggered, this, &FileMenu::save);
  connect(save_as_act_, &QAction::triggered, this, &FileMenu::saveAs);

  connect(close_view_act_, &QAction::triggered, this, &FileMenu::closeView);
  connect(close_all_act_, &QAction::triggered, this, &FileMenu::closeAll);
  connect(quit_act_, &QAction::triggered, this, &FileMenu::quit);

  addAction(open_act_);
  addAction(save_act_);
  addAction(save_as_act_);
  addSeparator();
  addAction(close_view_act_);
  addAction(close_all_act_);
  addAction(quit_act_);
}
