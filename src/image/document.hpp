#pragma once

#include <QObject>

// Forward declarations
class QUndoStack;

namespace imagecpp {

// Forward declarations
class ProImage;

/*
 * The intent of this class is to represent a document, an object that ties
 * together an image, a histogram and a history of changes. Also has information
 * about the image (name, filepath, format...)
 */
class Document : public QObject {
  Q_OBJECT

public:
  Document(ProImage *image = nullptr, QObject *parent = nullptr);
  Document(const Document &data);
  virtual ~Document();

  int id() const noexcept { return id_; }
  QString filePath() const { return file_path_; }

  ProImage *image() { return image_; }
  QUndoStack *undoStack() { return undo_stack_; }

  ProImage *copyImage() const;

  // TODO: get image format
  // TODO: get image size

signals:
  void filePathChanged(const QString &file_path);
  void imageUpdated(const ProImage *image);

public slots:
  void setFilePath(QString file_path);
  void setImage(ProImage *image);

protected:
  static int next_id_;

private:
  int id_{next_id_++};

  QString file_path_;

  ProImage *image_;
  QUndoStack *undo_stack_;
};

} // namespace imagecpp
