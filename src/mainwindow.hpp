#pragma once

#include <QMainWindow>

#include "manager/imagemanager.hpp"
#include "menus/editmenu.hpp"
#include "menus/filemenu.hpp"
#include "menus/imagemenu.hpp"
#include "statusbar/mainstatusbar.hpp"

class QUndoGroup;
class QMdiArea;
class FileMenu;
class EditMenu;
class ImageMenu;
class ProImage;
class QMdiArea;
class ImageDisplayArea;
class MainStatusBar;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~MainWindow();

signals:
  void activeImageChanged(ProImage *img);

private slots:
  void showDisplayArea(const ProImage *image);

private:
  void createMenus();
  void createStatusBar();

  ProImage *activeImage() const;

private:
  FileMenu file_menu_;
  EditMenu edit_menu_;
  ImageMenu image_menu_;

  MainStatusBar main_status_bar_;

  ImageManager image_manager_;

  QMdiArea *mdi_area_;
  QUndoGroup *undo_group_;

  ProImage *active_image_{nullptr};
};
