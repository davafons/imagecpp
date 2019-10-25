#pragma once

#include <QMenuBar>

#include "widgets/menus/editmenu.hpp"
#include "widgets/menus/filemenu.hpp"
#include "widgets/menus/imagemenu.hpp"
#include "widgets/menus/settingsmenu.hpp"
#include "widgets/menus/windowsmenu.hpp"

namespace imagecpp {

/*
 *
 */
class MainMenuBar : public QMenuBar {
  Q_OBJECT

public:
  MainMenuBar(QWidget *parent = nullptr);

signals:
  void open();
  void save();
  void saveAs();

  void closeView();
  void closeAll();
  void quit();

  void undo();
  void redo();
  void toggleRectSelect(bool toggled);

  void duplicateImage();
  void grayscale();
  void inverse();
  void linearTransform();
  void brightnessAndConstrast();
  void gammaCorrection();

  void toggleTabsView(bool toggled);

  void toggleHistoryWindow(bool toggled);

public slots:
  void createUndoActions(const QUndoGroup *undo_group = nullptr);

private:
  void createFileMenu();
  void createEditMenu();
  void createImageMenu();
  void createSettingsMenu();
  void createWindowsMenu();

private:
  FileMenu file_menu_;
  EditMenu edit_menu_;
  ImageMenu image_menu_;
  SettingsMenu settings_menu_;
  WindowsMenu windows_menu_;
};

} // namespace imagecpp
