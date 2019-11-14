#include "imagesubwindow.hpp"

#include <QStatusBar>

#include "image/document.hpp"
#include "image/image.hpp"
#include "widgets/image/imagedisplayarea.hpp"

namespace imagecpp {

ImageSubWindow::ImageSubWindow(Document *document)
    : display_(new ImageDisplayArea()), document_(document) {

  // Setup properties
  QString window_title = tr("(%1 x %2) %3")
                             .arg(document->dimensions().width())
                             .arg(document->dimensions().height())
                             .arg(document->filePath());
  setWindowTitle(window_title);

  setWidget(display_);

  display_->onImageOpened(document->image());

  // Make connections with the loaded objects

  connect(display_,
          &ImageDisplayArea::pixelInformation,
          this,
          &ImageSubWindow::pixelInformation);

  // Set the title of the window according to the name of the open document
  connect(document_, &Document::filePathChanged, this, &ImageSubWindow::setWindowTitle);

  connect(
      document_, &Document::imageChanged, display_, &ImageDisplayArea::onImageUpdated);

  connect(display_,
          &ImageDisplayArea::selectionCreated,
          document_,
          &Document::setSelection);
}

}  // namespace imagecpp
