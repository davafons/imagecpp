#pragma once

#include <QMainWindow>

#include "manager/imagemanager.hpp"
#include "widgets/menus/mainmenubar.hpp"
#include "widgets/statusbar/mainstatusbar.hpp"

// Forward declarations
class QUndoView;
class QUndoGroup;

namespace imagecpp {

// Forward declarations
class SubWindowsArea;

/*
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~MainWindow();

private:
  void createMenuBar();
  void createStatusBar();
  void createSubWindowsArea();

private:
  MainMenuBar main_menu_bar_;
  MainStatusBar main_status_bar_;

  ImageManager image_manager_;

  SubWindowsArea *mdi_area_{nullptr};

  QUndoGroup *undo_group_{nullptr};
  QUndoView *undo_view_{nullptr};
};

} // namespace imagecpp
