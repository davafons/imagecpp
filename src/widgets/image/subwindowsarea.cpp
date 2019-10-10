#include "subwindowsarea.hpp"

#include <QDebug>

#include "image/document.hpp"
#include "widgets/image/imagesubwindow.hpp"

namespace imagecpp {

SubWindowsArea::SubWindowsArea(QWidget *parent)
    : QMdiArea(parent), active_image_(nullptr) {

  setTabsClosable(true);
  setTabsMovable(true);

  connect(this, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *w) {
    active_image_ = imageFromSubwindow(w);

    emit activeImageChanged(active_image_);
  });
}

void SubWindowsArea::addDisplayArea(Document *data) {
  Q_CHECK_PTR(data);
  qInfo() << "Add new display area for data: " << data;

  ImageSubWindow *subwindow = new ImageSubWindow(data);
  Q_CHECK_PTR(subwindow);

  addSubWindow(subwindow);
  subwindow->show();

  emit displayAreaAdded(subwindow->display());
}

void SubWindowsArea::toggleTabsView(bool toggled) {
  if (toggled) {
    setViewMode(QMdiArea::TabbedView);
  } else {
    setViewMode(QMdiArea::SubWindowView);
  }
}

Document *SubWindowsArea::imageFromSubwindow(QMdiSubWindow *subwindow) {
  ImageSubWindow *active_subwindow =
      dynamic_cast<ImageSubWindow *>(activeSubWindow());

  if (active_subwindow) {
    return active_subwindow->data();
  }

  return nullptr;
}

} // namespace imagecpp
