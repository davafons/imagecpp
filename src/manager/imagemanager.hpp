#pragma once

// #include <QMap>
#include <QObject>

namespace imagecpp {

// Forward declarations
class ProImage;
class Document;

/*
 *
 */
class ImageManager : public QObject {
  Q_OBJECT

signals:
  void imageOpened(Document *data);
  void imageSaved(Document *data, const QString &file_path);

public slots:
  void open();
  void save(Document *image);
  void saveAs(Document *image, QString file_path = "");

  void duplicate(Document *other);

private:
  // QMap<int, Document*> loaded_images_;
  QString filters_ = tr("Image Files(*.png *.jpg *.jpeg *.bmp)");
};

} // namespace imagecpp
