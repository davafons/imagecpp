#pragma once

#include <QAction>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>

#include <QMdiArea>

#include "image/imagedisplayarea.hpp"
#include "image/proimage.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());

public slots:
  void pixelMouseOver(const QPoint &point, const QColor &color);

private slots:
  void open();
  // void save();
  // void saveAs();

  void resetSize();

private:
  void createActions();
  void createMenus();

  ImageDisplayArea *getActiveImageDisplayArea() const;

private:
  QMenu *file_menu_;

  QAction *quit_act_;
  QAction *open_act_;
  QAction *save_act_;
  QAction *save_as_act_;

  QMenu *options_menu_;

  QAction *toggle_subtabs_act_;
  QAction *reset_size_act_;

  QMdiArea *mdi_area_;

  QLabel *colorLabel_;
  QLabel *pixelLabel_;
};
