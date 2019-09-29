#pragma once

#include <QMenu>

class FileMenu : public QMenu {
public:
  FileMenu(const QString &title = tr("&File"), QWidget *parent = nullptr);
  virtual ~FileMenu() = default;

  QAction *openAct() const { return open_act_; }
  QAction *saveAct() const { return save_act_; }
  QAction *saveAsAct() const { return save_as_act_; }
  QAction *quitAct() const { return quit_act_; }

private:
  QAction *open_act_;
  QAction *save_act_;
  QAction *save_as_act_;
  QAction *quit_act_;
};
