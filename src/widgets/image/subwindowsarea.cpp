#include "subwindowsarea.hpp"

#include "widgets/image/imagesubwindow.hpp"

SubWindowsArea::SubWindowsArea(QWidget *parent) : QMdiArea(parent) {
  setTabsClosable(true);
  setTabsMovable(true);

  connect(this, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *w) {
    active_image_ = imageFromSubwindow(w);

    emit activeImageChanged(active_image_);
  });
}

void SubWindowsArea::addDisplayArea(ImageData *data) {
  ImageSubWindow *subwindow = new ImageSubWindow(data);
  addSubWindow(subwindow);
  subwindow->show();

  emit displayAreaAdded(subwindow->display());
}

ImageData *SubWindowsArea::imageFromSubwindow(QMdiSubWindow *subwindow) {
  ImageSubWindow *active_subwindow =
      dynamic_cast<ImageSubWindow *>(activeSubWindow());

  if (active_subwindow) {
    return active_subwindow->data();
  }

  return nullptr;
}
