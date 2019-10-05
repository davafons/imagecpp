#pragma once

#include <QMdiArea>

class ImageData;
class ImageDisplayArea;

class SubWindowsArea : public QMdiArea {
  Q_OBJECT

signals:
  void activeImageChanged(ImageData *image_data);
  void displayAreaAdded(ImageDisplayArea *display_area);

public:
  SubWindowsArea(QWidget *parent = nullptr);
  virtual ~SubWindowsArea() = default;

  ImageData *activeImage() const { return active_image_; }

public slots:
  void addDisplayArea(ImageData *data);

private:
  ImageData *imageFromSubwindow(QMdiSubWindow *subwindow);

private:
  ImageData *active_image_{nullptr};
};
