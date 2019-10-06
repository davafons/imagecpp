#pragma once

#include <QMdiSubWindow>

#include "widgets/image/imagedisplayarea.hpp"

class ImageData;

class ImageSubWindow : public QMdiSubWindow {
  Q_OBJECT
public:
  ImageSubWindow(ImageData *data);

  ImageData *data() { return data_; }
  ImageDisplayArea *display() { return display_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

private:
  ImageDisplayArea *display_{nullptr};
  ImageData *data_{nullptr}; // Make a const pointer?
};
