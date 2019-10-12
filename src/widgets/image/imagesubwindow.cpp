#include "imagesubwindow.hpp"

#include "image/document.hpp"
#include "image/image.hpp"
#include "widgets/image/imagedisplayarea.hpp"

namespace imagecpp {

ImageSubWindow::ImageSubWindow(Document *document)
    : display_(new ImageDisplayArea()), document_(document) {

  // Setup properties
  setWindowTitle(document->filePath());
  setWidget(display_);

  display_->onImageOpened(document->image());

  // Make connections with the loaded objects

  connect(display_, &ImageDisplayArea::pixelInformation, this,
          &ImageSubWindow::pixelInformation);

  // Set the title of the window according to the name of the open document
  connect(document_, &Document::filePathChanged, this,
          &ImageSubWindow::setWindowTitle);

  connect(document_, &Document::imageChanged, display_,
          &ImageDisplayArea::onImageUpdated);
}

} // namespace imagecpp
