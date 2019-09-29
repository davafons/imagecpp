#pragma once

#include <QMainWindow>

class FileMenu;
class ProImage;
class QMdiArea;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());

private slots:
  void open();
  void save();

  void addImageDisplayArea(const ProImage *image);

private:
  void createMenus();
  void connectMenus();

private:
  FileMenu *file_menu_;

  QMdiArea *mdi_area_;
};
