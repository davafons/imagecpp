#pragma once

#include <QMdiSubWindow>

namespace imagecpp {

// Forward declarations
class Document;
class ImageDisplayArea;

/*
 *
 */
class ImageSubWindow : public QMdiSubWindow {
  Q_OBJECT
public:
  ImageSubWindow(Document *data);

  Document *data() { return data_; }
  ImageDisplayArea *display() { return display_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

private:
  ImageDisplayArea *const display_;
  Document *const data_;
};

} // namespace imagecpp
