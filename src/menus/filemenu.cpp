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

  quit_act_ = new QAction(tr("&Quit"), this);
  quit_act_->setShortcut(QKeySequence::Quit);
  quit_act_->setStatusTip(tr("Quit from the application"));

  addSeparator();

  connect(open_act_, &QAction::triggered, this, &FileMenu::open);
  connect(save_act_, &QAction::triggered, this, &FileMenu::save);
  connect(save_as_act_, &QAction::triggered, this, &FileMenu::saveAs);
  connect(quit_act_, &QAction::triggered, this, &FileMenu::quit);

  addAction(open_act_);
  addAction(save_act_);
  addAction(save_as_act_);
  addSeparator();
  addAction(quit_act_);
}
