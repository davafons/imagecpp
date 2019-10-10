#include "imagesubwindow.hpp"

#include "image/document.hpp"
#include "image/proimage.hpp"
#include "widgets/image/imagedisplayarea.hpp"

namespace imagecpp {

ImageSubWindow::ImageSubWindow(Document *data)
    : display_(new ImageDisplayArea()), data_(data) {
  setWidget(display_);

  display_->onImageOpened(data->image());
  setWindowTitle(data->filePath());

  connect(display_, &ImageDisplayArea::pixelInformation, this,
          &ImageSubWindow::pixelInformation);

  connect(data_, &Document::filePathChanged, this,
          &ImageSubWindow::setWindowTitle);

  connect(data_, &Document::imageUpdated, display_,
          &ImageDisplayArea::onImageUpdated);
}

} // namespace imagecpp
