#include "imagesubwindow.hpp"

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

ImageSubWindow::ImageSubWindow(ImageData *data)
    : display_(new ImageDisplayArea()), data_(data) {
  setWidget(display_);

  display_->setImage(data->image());
  setWindowTitle(data->filePath());

  connect(display_, &ImageDisplayArea::pixelInformation, this,
          &ImageSubWindow::pixelInformation);

  connect(data_, &ImageData::filePathChanged, this,
          &ImageSubWindow::setWindowTitle);

  connect(data_, &ImageData::imageChanged, display_,
          &ImageDisplayArea::onImageChanged);
}
