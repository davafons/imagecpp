#pragma once

#include <QMainWindow>

class FileMenu;
class ProImage;
class QMdiArea;
class ImageDisplayArea;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());

private slots:
  void open();
  void save();
  void saveAs();

  void addImageDisplayArea(const ProImage *image);

private:
  void createMenus();
  void connectMenus();

  ProImage *activeImage() const;

private:
  FileMenu *file_menu_;

  QMdiArea *mdi_area_;
};
