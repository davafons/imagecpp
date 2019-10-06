#pragma once

#include <QMainWindow>

#include "manager/imagemanager.hpp"
#include "widgets/menus/editmenu.hpp"
#include "widgets/menus/filemenu.hpp"
#include "widgets/menus/imagemenu.hpp"
#include "widgets/menus/settingsmenu.hpp"
#include "widgets/menus/windowsmenu.hpp"
#include "widgets/statusbar/mainstatusbar.hpp"

class SubWindowsArea;
class QUndoView;
class QUndoGroup;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~MainWindow();

private:
  void createMenus();
  void createStatusBar();
  void createSubWindowsArea();

private:
  // Visual widgets
  FileMenu file_menu_;
  EditMenu edit_menu_;
  ImageMenu image_menu_;
  SettingsMenu settings_menu_;
  WindowsMenu windows_menu_;
  MainStatusBar main_status_bar_;

  SubWindowsArea *mdi_area_{nullptr};

  ImageManager image_manager_;

  QUndoGroup *undo_group_{nullptr};
  QUndoView *undo_view_{nullptr};
};
