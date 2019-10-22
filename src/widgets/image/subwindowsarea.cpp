#include "subwindowsarea.hpp"

#include <QDebug>

#include "image/document.hpp"
#include "widgets/image/imagesubwindow.hpp"

namespace imagecpp {

SubWindowsArea::SubWindowsArea(QWidget *parent)
    : QMdiArea(parent), active_document_(nullptr) {

  setTabsClosable(true);
  setTabsMovable(true);

  connect(this, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *w) {
    active_document_ = documentFromSubwindow(w);

    emit activeDocumentChanged(active_document_);
  });
}
//
// ImageSubWindow *SubWindowsArea::activeSubWindow() const {
//   return static_cast<ImageSubWindow *>(QMdiArea::activeSubWindow());
// }

void SubWindowsArea::addDocumentWindow(Document *document) {
  Q_CHECK_PTR(document);
  qInfo() << "Add new display area for document: " << document;

  ImageSubWindow *subwindow = new ImageSubWindow(document);
  Q_CHECK_PTR(subwindow);

  addSubWindow(subwindow);
  subwindow->show();

  emit subwindowAdded(subwindow);
}

void SubWindowsArea::toggleTabsView(bool toggled) {
  if (toggled) {
    setViewMode(QMdiArea::TabbedView);
  } else {
    setViewMode(QMdiArea::SubWindowView);
  }
}

Document *SubWindowsArea::documentFromSubwindow(QMdiSubWindow *subwindow) {
  ImageSubWindow *active_subwindow =
      dynamic_cast<ImageSubWindow *>(activeSubWindow());

  if (active_subwindow) {
    return active_subwindow->document();
  }

  return nullptr;
}

} // namespace imagecpp
