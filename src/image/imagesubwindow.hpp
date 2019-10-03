#pragma once

#include <QMdiSubWindow>

#include "image/imagedata.hpp"
#include "image/imagedisplayarea.hpp"

/*
 * Links an image with its window representation
 */
class ImageSubWindow : public QMdiSubWindow {
public:
  ImageSubWindow(ImageData *data)
      : display_(new ImageDisplayArea()), data_(data) {
    setWidget(display_);
  }

  ImageData *data() { return data_; }

private:
  ImageDisplayArea *display_;
  ImageData *data_;
};
