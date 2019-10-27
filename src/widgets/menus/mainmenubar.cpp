#include "mainmenubar.hpp"

namespace imagecpp {

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
  connect(
      &edit_menu_, &EditMenu::toggleRectSelect, this, &MainMenuBar::toggleRectSelect);
}

void MainMenuBar::createImageMenu() {
  addMenu(&image_menu_);

  connect(&image_menu_, &ImageMenu::showHistogram, this, &MainMenuBar::showHistogram);
  connect(&image_menu_, &ImageMenu::duplicateImage, this, &MainMenuBar::duplicateImage);
  connect(&image_menu_, &ImageMenu::grayscale, this, &MainMenuBar::grayscale);
  connect(&image_menu_, &ImageMenu::inverse, this, &MainMenuBar::inverse);
  connect(
      &image_menu_, &ImageMenu::linearTransform, this, &MainMenuBar::linearTransform);
  connect(&image_menu_,
          &ImageMenu::brightnessAndConstrast,
          this,
          &MainMenuBar::brightnessAndConstrast);
  connect(
      &image_menu_, &ImageMenu::gammaCorrection, this, &MainMenuBar::gammaCorrection);
}

void MainMenuBar::createSettingsMenu() {
  addMenu(&settings_menu_);

  connect(&settings_menu_,
          &SettingsMenu::toggleTabsView,
          this,
          &MainMenuBar::toggleTabsView);
}

void MainMenuBar::createWindowsMenu() {
  addMenu(&windows_menu_);

  connect(&windows_menu_,
          &WindowsMenu::toggleHistoryWindow,
          this,
          &MainMenuBar::toggleHistoryWindow);
}

}  // namespace imagecpp
