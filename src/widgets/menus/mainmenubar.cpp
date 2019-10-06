#include "mainmenubar.hpp"

MainMenuBar::MainMenuBar(QWidget *parent) {
  createFileMenu();
  createEditMenu();
  createImageMenu();
  createSettingsMenu();
  createWindowsMenu();
}

void MainMenuBar::createUndoActions(const QUndoGroup *undo_group) {
  edit_menu_.createUndoActions(undo_group);
}

void MainMenuBar::createFileMenu() {
  addMenu(&file_menu_);

  connect(&file_menu_, &FileMenu::open, this, &MainMenuBar::open);
  connect(&file_menu_, &FileMenu::save, this, &MainMenuBar::save);
  connect(&file_menu_, &FileMenu::saveAs, this, &MainMenuBar::saveAs);

  connect(&file_menu_, &FileMenu::closeView, this, &MainMenuBar::closeView);
  connect(&file_menu_, &FileMenu::closeAll, this, &MainMenuBar::closeAll);
  connect(&file_menu_, &FileMenu::quit, this, &MainMenuBar::quit);
}

void MainMenuBar::createEditMenu() {
  addMenu(&edit_menu_);

  connect(&edit_menu_, &EditMenu::undo, this, &MainMenuBar::undo);
  connect(&edit_menu_, &EditMenu::redo, this, &MainMenuBar::redo);
}

void MainMenuBar::createImageMenu() {
  addMenu(&image_menu_);

  connect(&image_menu_, &ImageMenu::toGrayscale, this,
          &MainMenuBar::toGrayscale);
  connect(&image_menu_, &ImageMenu::duplicateImage, this,
          &MainMenuBar::duplicateImage);
}

void MainMenuBar::createSettingsMenu() {
  addMenu(&settings_menu_);

  connect(&settings_menu_, &SettingsMenu::toggleTabsView, this,
          &MainMenuBar::toggleTabsView);
}

void MainMenuBar::createWindowsMenu() {
  addMenu(&windows_menu_);

  connect(&windows_menu_, &WindowsMenu::toggleHistoryWindow, this,
          &MainMenuBar::toggleHistoryWindow);
}
