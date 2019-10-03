#pragma once

#include <QMdiSubWindow>

#include "image/imagedata.hpp"
#include "image/imagedisplayarea.hpp"

/*
 * Links an image with its window representation
 */
class ImageSubWindow : public QMdiSubWindow {
  Q_OBJECT
public:
  ImageSubWindow(ImageData *data)
      : display_(new ImageDisplayArea()), data_(data) {
    setWidget(display_);

    display_->setImage(data->image());

    connect(display_, &ImageDisplayArea::pixelInformation, this,
            &ImageSubWindow::pixelInformation);
  }

  ImageData *data() { return data_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

private:
  ImageDisplayArea *display_;
  ImageData *data_;
};
