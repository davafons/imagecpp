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
  // ImageSubWindow *activeSubWindow() const;


signals:
  void activeDocumentChanged(Document *image_document);
  // void activeSubWindowChanged(ImageSubWindow *subwindow);

  void subwindowAdded(ImageSubWindow *subwindow);

public slots:
  void addDocumentWindow(Document *document);
  void toggleTabsView(bool toggled);

private:
  Document *documentFromSubwindow(QMdiSubWindow *subwindow);

private:
  Document *active_document_;
};

} // namespace imagecpp
