#pragma once

#include <QMainWindow>

class FileMenu;
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

signals:
  void activeImageChanged(ProImage *img);

private slots:
  void open();
  void save();
  void saveAs();

  void addImageDisplayArea(const ProImage *image);

private:
  void createMenus();
  void createStatusBar();

  ProImage *activeImage() const;

private:
  FileMenu *file_menu_;
  ImageMenu *image_menu_;

  MainStatusBar *main_status_bar_;

  ProImage *active_image_{nullptr};
  QMdiArea *mdi_area_;
};
