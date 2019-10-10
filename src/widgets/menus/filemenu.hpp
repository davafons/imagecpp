#pragma once

#include <QMenu>

namespace imagecpp {

/*
 */
class FileMenu : public QMenu {
  Q_OBJECT

public:
  explicit FileMenu(QWidget *parent = nullptr);
  virtual ~FileMenu() = default;

signals:
  void open();
  void save();
  void saveAs();

  void closeView();
  void closeAll();
  void quit();

private:
  QAction *open_act_;
  QAction *save_act_;
  QAction *save_as_act_;

  QAction *close_view_act_;
  QAction *close_all_act_;
  QAction *quit_act_;
};

} // namespace imagecpp
