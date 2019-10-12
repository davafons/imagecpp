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
  ImageSubWindow(Document *document);

  // Getters
  Document *document() { return document_; }
  ImageDisplayArea *display() { return display_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

private:
  ImageDisplayArea *const display_;
  Document *const document_;
};

} // namespace imagecpp
