#pragma once

#include <QMdiArea>

namespace imagecpp {

// Forward declarations
class Document;
class ImageSubWindow;

/*
 */
class SubWindowsArea : public QMdiArea {
  Q_OBJECT

public:
  SubWindowsArea(QWidget *parent = nullptr);
  virtual ~SubWindowsArea() = default;

  Document *activeDocument() const { return active_document_; }

signals:
  void activeDocumentChanged(Document *image_document);
  void subwindowAdded(ImageSubWindow *subwindow);

public slots:
  void addDisplayArea(Document *document);
  void toggleTabsView(bool toggled);

private:
  Document *imageFromSubwindow(QMdiSubWindow *subwindow);

private:
  Document *active_document_;
};

} // namespace imagecpp
