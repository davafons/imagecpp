#pragma once

#include <QMdiArea>

namespace imagecpp {

// Forward declarations
class Document;
class ImageDisplayArea;

/*
 */
class SubWindowsArea : public QMdiArea {
  Q_OBJECT

signals:
  void activeImageChanged(Document *image_data);
  void displayAreaAdded(ImageDisplayArea *display_area);

public:
  SubWindowsArea(QWidget *parent = nullptr);
  virtual ~SubWindowsArea() = default;

  Document *activeImage() const { return active_image_; }

public slots:
  void addDisplayArea(Document *data);
  void toggleTabsView(bool toggled);

private:
  Document *imageFromSubwindow(QMdiSubWindow *subwindow);

private:
  Document *active_image_;
};

} // namespace imagecpp
