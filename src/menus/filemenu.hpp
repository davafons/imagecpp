#pragma once

#include <QMenu>

class FileMenu : public QMenu {
  Q_OBJECT

public:
  explicit FileMenu(const QString &title = tr("&File"),
                    QWidget *parent = nullptr);
  virtual ~FileMenu() = default;

signals:
  void open();
  void save();
  void saveAs();
  void quit();

private:
  QAction *open_act_;
  QAction *save_act_;
  QAction *save_as_act_;
  QAction *quit_act_;
};
