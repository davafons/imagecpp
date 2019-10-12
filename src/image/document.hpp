#pragma once

#include <QObject>

#include "histogram.hpp"

// Forward declarations
class QUndoStack;

namespace imagecpp {

// Forward declarations
class Image;

/*
 * The intent of this class is to represent a document, an object that ties
 * together an image, a histogram and a history of changes. Also has information
 * about the image (name, filepath, format...)
 */
class Document : public QObject {
  Q_OBJECT

public:
  Document(Image *image = nullptr, QObject *parent = nullptr);
  Document(const Document &data);
  virtual ~Document();

  int id() const noexcept { return id_; }
  QString filePath() const { return file_path_; }

  Image *image() { return image_; }
  QUndoStack *undoStack() { return undo_stack_; }
  Histogram *histogram() { return histogram_; }

  Image *copyImage() const;

  // TODO: get image format
  // TODO: get image size

signals:
  void filePathChanged(const QString &file_path);
  void imageUpdated(const Image *image);

public slots:
  void setFilePath(QString file_path);
  void setImage(Image *image);

protected:
  static int next_id_;

private:
  int id_{next_id_++};

  QString file_path_;

  Image *image_;
  QUndoStack *undo_stack_;
  Histogram *histogram_;
};

} // namespace imagecpp
