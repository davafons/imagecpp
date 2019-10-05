#pragma once

#include <QMdiSubWindow>

#include "widgets/image/imagedisplayarea.hpp"

class ImageData;

/*
 * Links an image with its window representation
 */
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
  ImageData *data_{nullptr}; // Make const pointer? (not pointer to const)
};
