#pragma once

// #include <QMap>
#include <QObject>

namespace imagecpp {

// Forward declarations
class Image;
class Document;

/*
 *
 */
class DocumentsManager : public QObject {
  Q_OBJECT

signals:
  void newDocumentOpened(Document *data) const;
  void documentSaved(Document *data, const QString &file_path) const;

public slots:
  void open();
  void save(Document *document) const;
  void saveAs(Document *document, QString file_path = "") const;

  void duplicate(Document *other) const;

private:
  // QMap<int, Document*> loaded_images_;
  QString filters_ = tr("Image Files(*.png *.jpg *.jpeg *.bmp)");
};

} // namespace imagecpp
